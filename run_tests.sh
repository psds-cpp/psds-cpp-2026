#!/usr/bin/env bash
# Build and run tests for tasks
#
# Using:
#   ./run_tests.sh addition           single task
#   ./run_tests.sh addition rms       multiple tasks
#   ./run_tests.sh week_02            all tasks in week_02
#   ./run_tests.sh all                all tasks in all weeks
#   ./run_tests.sh --changed [SHA]    tasks changed after commit SHA
#                                     (without SHA — last commit)
#
# Options:
#   -b, --build-dir <dir>             build directory (default: build)
#   -h, --help                        show help information

set -uo pipefail

usage() {
  sed -n '2,15p' "$0" | sed 's/^# \{0,1\}//';
}

is_ci () {
  [[ "${GITHUB_ACTIONS:-}" == true ]];
}

crash() {
  if is_ci; then
    echo "::error::$*" >&2;
  else
    echo "❌ $*" >&2;
  fi
  exit 2
}

join() {
  local out
  printf -v out '%s, ' "$@"
  echo "${out%, }"
}

week_tasks() {
  local cmake_file="$1/tasks/CMakeLists.txt"
  if [[ -f "$cmake_file" ]]; then
    { cat "$cmake_file"; echo; } |
      sed -nE 's/^[[:space:]]*add_subdirectory[[:space:]]*\([[:space:]]*([A-Za-z0-9_]+).*/\1/p'
  else
    local dir
    for dir in "$1"/tasks/*/; do
      [[ -d "$dir" ]] && basename "$dir"
    done
  fi
}

all_tasks() {
  local week
  for week in week_*/; do
    [[ -d "$week/tasks" ]] && week_tasks "${week%/}"
  done
}

changed_tasks() {
  local files
  if [[ -n "$BASE" && ! "$BASE" =~ ^0+$ ]] && git cat-file -e "$BASE^{commit}" 2>/dev/null; then
    files=$(git diff --name-only "$BASE" HEAD)     # all push commits
  elif git rev-parse -q --verify HEAD~1 >/dev/null; then
    files=$(git diff --name-only HEAD~1 HEAD)      # only last commit
  else
    files=$(git ls-files)                          # the first commit
  fi
  echo "Changed files:" >&2
  echo "$files" >&2
  grep -oE '^week_[^/]+/tasks/[^/]+/' <<< "$files" | cut -d/ -f3 || true
}

declare -A added_tasks=()
tasks=()
add_tasks() {
  local task
  for task in "$@"; do
    if [[ -z "${added_tasks[$task]:-}" ]]; then
      added_tasks[$task]=1
      tasks+=("$task")
    fi
  done
}

# --- Parsing arguments ---

cd "$(dirname "$0")" || exit 2

BUILD_DIR=build
CHANGED=false
BASE=
targets=()

while (( $# > 0 )); do
  case "$1" in
    -h|--help)
      usage
      exit 0
      ;;
    -b|--build-dir)
      [[ -n "${2:-}" ]] || crash "--build-dir requires value <dir>"
      BUILD_DIR=$2
      shift
      ;;
    --changed)
      CHANGED=true
      if [[ "${2:-}" =~ ^[0-9a-f]{7,40}$ ]]; then   # необязательный SHA
        BASE=$2
        shift
      fi
      ;;
    -*)
      crash "Unknown option: $1 (see --help)"
      ;;
    *)
      targets+=("$1")
      ;;
  esac
  shift
done

if ! $CHANGED && (( ${#targets[@]} == 0 )); then
  usage
  exit 2
fi

# --- Make task list ---

if $CHANGED; then
  declare -A is_changed=()
  for task in $(changed_tasks); do
    is_changed[$task]=1
  done
  for task in $(all_tasks); do
    [[ -n "${is_changed[$task]:-}" ]] && add_tasks "$task"
  done
fi

for target in "${targets[@]}"; do
  [[ "$target" =~ ^[A-Za-z0-9_]+$ ]] || crash "Unknown name: '$target'"

  if [[ "$target" == all ]]; then
    mapfile -t found < <(all_tasks)
  elif [[ "$target" == week_* ]]; then
    [[ -d "$target/tasks" ]] || crash "There is no directory $target/tasks"
    mapfile -t found < <(week_tasks "$target")
  else
    compgen -G "week_*/tasks/$target/" > /dev/null || crash "Task '$target' is not found"
    found=("$target")
  fi

  add_tasks "${found[@]}"
done

label=$(join "${targets[@]}")
$CHANGED && label="changed${label:+, $label}"
echo "Targets: $label"
echo "Tasks to test: '${tasks[*]}'"

# --- Configure ---

if (( ${#tasks[@]} > 0 )) && [[ ! -f "$BUILD_DIR/CMakeCache.txt" ]]; then
  echo "=== Configuring project in $BUILD_DIR ==="
  cmake -B "$BUILD_DIR" || crash "cmake configure FAILED"
fi

# --- Build and run ---

declare -i passed_count=0
declare -i failed_count=0
declare -i task_count=0

passed_tasks=()
failed_tasks=()

echo "=== Starting tests for selected tasks ==="

for task in "${tasks[@]}"; do
  task_count+=1
  is_ci && echo "::group::$task"
  echo "=== Processing $task ==="

  if cmake --build "$BUILD_DIR" --target "test_$task" --parallel; then
    echo "✅ test_$task built successfully"

    if "$BUILD_DIR/tasks/test_$task"; then
      echo "✅ test_$task PASSED"
      passed_count+=1
      passed_tasks+=("$task")
    else
      echo "❌ test_$task FAILED"
      is_ci && echo "::error title=$task::test_$task FAILED"
      failed_count+=1
      failed_tasks+=("$task")
    fi
  else
    echo "❌ test_$task build FAILED"
    is_ci && echo "::error title=$task::test_$task build FAILED"
    failed_count+=1
    failed_tasks+=("$task")
  fi

  is_ci && echo "::endgroup::"
done

# --- Summary ---

echo "=== Test Results Summary ==="
echo "Total tasks in list: ${#tasks[@]}"
echo "Processed: $task_count"
echo "✅ Passed: $passed_count [$(join "${passed_tasks[@]}")]"
echo "❌ Failed: $failed_count [$(join "${failed_tasks[@]}")]"

if [[ -n "${GITHUB_STEP_SUMMARY:-}" ]] && (( task_count > 0 )); then
  {
    echo "### Test Results: $label"
    echo "| Task | Result |"
    echo "|---|---|"
    for task in "${passed_tasks[@]}"; do echo "| $task | ✅ |"; done
    for task in "${failed_tasks[@]}"; do echo "| $task | ❌ |"; done
  } >> "$GITHUB_STEP_SUMMARY"
fi

if [ $failed_count -gt 0 ]; then
  echo "❌ Some tasks failed!"
  exit 1
elif [ $task_count -eq 0 ]; then
  echo "No tasks were processed (no changes)"
  exit 0
else
  echo "✅ All processed tasks passed!"
  exit 0
fi