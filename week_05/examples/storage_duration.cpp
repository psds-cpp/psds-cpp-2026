#include <iostream>
#include <vector>

int global_zero;                // bss
int global_init = 18;           // data
const int global_const = 10;    // rodata

int global_zero_2;                // bss
int global_init_2 = 18;           // data
const int global_const_2 = 10;    // rodata

static int static_zero;
static int static_init = 18;

const char* str_a = "hello";
const char* str_b = "hello";

thread_local int tlocal_var = 10;

void local_var(int func_arg, const int func_arg_const, int& ref, const int& ref_const) {
    std::cout << __func__ << ':' << std::endl;
    int local = 18;
    const int local_const = 10;
    std::cout << "addr func_arg = \t" << &func_arg << std::endl;
    std::cout << "addr func_arg_const = \t" << &func_arg_const << std::endl;
    std::cout << "addr ref = \t\t" << &ref << std::endl;
    std::cout << "addr ref_const = \t" << &ref_const << std::endl;
    std::cout << "addr local = \t\t" << &local << std::endl;
    std::cout << "addr local_const = \t" << &local_const << std::endl;
    const int local_const_2 = 20;
    int local_two = 2;
    std::cout << "addr local_const_2 = \t" << &local_const_2 << std::endl;
    std::cout << "addr local_two = \t" << &local_two << std::endl;
    std::cout << std::endl;
}

void same_literals() {
    std::cout << __func__ << ':' << std::endl;
    const char* str_c = "hello";

    std::cout << "addr str_a = \t" << &str_a << std::endl;
    std::cout << "addr str_b = \t" << &str_b << std::endl;
    std::cout << "addr str_c = \t" << &str_c << std::endl;
    std::cout << std::endl;
}

class Static {
public:
    static int* get_static_class_var() {
        return &static_class_var;
    }
private:
    static int static_class_var;
};

int Static::static_class_var = 0;

void static_var() {
    std::cout << __func__ << ':' << std::endl;
    static int static_local_var = 10;

    std::cout << "addr static_zero = \t\t" << &static_zero << std::endl;
    std::cout << "addr static_init = \t\t" << &static_init << std::endl;
    std::cout << "addr static_local_var = \t" << &static_local_var << std::endl;
    std::cout << "addr static_class_var = \t" << Static::get_static_class_var() << std::endl;
    std::cout << std::endl;
}

void dynamic_var() {
    std::cout << __func__ << ':' << std::endl;

    int* dynamic_var = new int;
    *dynamic_var = 10;
    int* dynamic_var_init = new int(10);
    int* dynamic_arr = new int[10]{};
    int* dynamic_var_init2 = new int{2};
    std::cout << "addr dynamic_var = \t" << dynamic_var << std::endl;
    std::cout << "addr dynamic_var_init = " << dynamic_var_init << std::endl;
    std::cout << "addr dynamic_arr = \t" << dynamic_arr << std::endl;
    std::cout << "addr dynamic_var_init2 = " << dynamic_var_init2 << std::endl;
    delete dynamic_var;
    delete dynamic_var_init;
    delete[] dynamic_arr;
    delete dynamic_var_init2;
    std::cout << std::endl;
}

void thread_var() {
    std::cout << __func__ << ':' << std::endl;
    int local_var;
    std::cout << "addr tlocal_var = \t" << &tlocal_var << std::endl;
    std::cout << "addr global_zero = \t" << &global_zero << std::endl;
    std::cout << "addr local_var = \t" << &local_var << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "global var:" << std::endl;
    std::cout << "addr global_zero =    " << &global_zero << std::endl;
    std::cout << "addr global_zero_2 =  " << &global_zero_2 << std::endl;
    std::cout << "addr global_init =    " << &global_init << std::endl;
    std::cout << "addr global_init_2 =  " << &global_init_2 << std::endl;
    std::cout << "addr global_const =   " << &global_const << std::endl;
    std::cout << "addr global_const_2 = " << &global_const_2 << std::endl;
    std::cout << std::endl;

    std::cout << "func:" << std::endl;
    std::cout << "addr func local_var =    " << (void*)&local_var << std::endl;
    std::cout << "addr func main =         " << (void*)&main << std::endl;
    std::cout << "addr func static class = " << (void*)&Static::get_static_class_var << std::endl;
    std::cout << std::endl;

    std::cout << "local var main:" << std::endl;
    int main_var = 0;
    const int main_var_const = 0;
    std::cout << "addr main_var =       " << &main_var << std::endl;
    std::cout << "addr main_var_const = " << &main_var_const << std::endl;
    std::cout << std::endl;

    local_var(main_var, main_var_const, main_var, main_var_const);
    same_literals();
    static_var();
    dynamic_var();
    thread_var();
}


