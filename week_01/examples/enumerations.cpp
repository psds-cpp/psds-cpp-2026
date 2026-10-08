#include <bitset>
#include <cstdint>
#include <iostream>
#include <type_traits>


enum CommandTypeE {
    CT_INIT,
    CT_UPDATE,
    CT_FINISH
};

enum class CommandTypeEC {
    INIT,
    UPDATE,
    FINISH
};

void unscoped_enum() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "CT_INIT = " << CT_INIT << std::endl;
    std::cout << "CT_UPDATE = " << CT_UPDATE << std::endl;
    std::cout << "CT_FINISH = " << CT_FINISH << std::endl;

    std::cout << "::CT_INIT = " << ::CT_INIT << std::endl;
    std::cout << "::CT_UPDATE = " << ::CT_UPDATE << std::endl;
    std::cout << "::CT_FINISH = " << ::CT_FINISH << std::endl;

    std::cout << "::CommandTypeE::CT_INIT = " << ::CommandTypeE::CT_INIT << std::endl; // unused CommandTypeE
    std::cout << "::CommandTypeE::CT_UPDATE = " << ::CommandTypeE::CT_UPDATE << std::endl;
    std::cout << "::CommandTypeE::CT_FINISH = " << ::CommandTypeE::CT_FINISH << std::endl;
    std::cout << std::endl;
}

void scoped_enum() {
    std::cout << __func__ << ':' << std::endl;
    // std::cout << "INIT = " << INIT << std::endl; // compile error
    // std::cout << "CommandTypeEC::INIT = " << CommandTypeEC::INIT << std::endl; // compile error
    std::cout << "CommandTypeEC::INIT = " << static_cast<int>(CommandTypeEC::INIT) << std::endl; // ok
    std::cout << "CommandTypeEC::UPDATE = " << static_cast<int>(CommandTypeEC::UPDATE) << std::endl; // ok
    std::cout << "CommandTypeEC::FINISH = " << static_cast<int>(CommandTypeEC::FINISH) << std::endl; // ok

    std::cout << std::endl;
}

void underlying_type_enum() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "type of CommandTypeE = " << typeid(CommandTypeE).name() << std::endl;
    std::cout << "type of CommandTypeEC = " << typeid(CommandTypeEC).name() << std::endl;
    std::cout << "type of value CommandTypeE = " << typeid(CT_INIT).name() << std::endl;
    std::cout << "type of value CommandTypeEC = " << typeid(CommandTypeEC::INIT).name() << std::endl;
    std::cout << std::endl;

    std::cout << "underlying type of CommandTypeE = "
        << typeid(std::underlying_type<CommandTypeE>::type).name() << std::endl;
    std::cout << "underlying type of CommandTypeEC = "
        << typeid(std::underlying_type<CommandTypeEC>::type).name() << std::endl;
    std::cout << std::endl;

    std::cout << std::boolalpha;
    std::cout << "underlying type of CommandTypeE is int ? "
    << std::is_same<std::underlying_type<CommandTypeE>::type, int>::value << std::endl;
    std::cout << "underlying type of CommandTypeEC is int ? "
        << std::is_same<std::underlying_type<CommandTypeEC>::type, int>::value << std::endl;
    std::cout << "underlying type of CommandTypeE is uint ? "
        << std::is_same<std::underlying_type<CommandTypeE>::type, unsigned>::value << std::endl;
    std::cout << "underlying type of CommandTypeEC is uint ? "
        << std::is_same<std::underlying_type<CommandTypeEC>::type, unsigned>::value << std::endl;
    std::cout << std::endl;

    std::cout << "CommandTypeE is enum ? " << std::is_enum<CommandTypeE>::value << std::endl;
    std::cout << "CommandTypeEC is enum ? " << std::is_enum<CommandTypeEC>::value << std::endl;
    std::cout << "CommandTypeE is integral ? " << std::is_integral<CommandTypeE>::value << std::endl;
    std::cout << "CommandTypeEC is integral ? " << std::is_integral<CommandTypeEC>::value << std::endl;
    std::cout << "CommandTypeE is arithmetic ? " << std::is_arithmetic<CommandTypeE>::value << std::endl;
    std::cout << "CommandTypeEC is arithmetic ? " << std::is_arithmetic<CommandTypeEC>::value << std::endl;
    std::cout << std::endl;
    std::cout << std::noboolalpha;
}

void arithmetic_operations() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "CT_INIT + CT_UPDATE + CT_FINISH = " << CT_INIT + CT_UPDATE + CT_FINISH << std::endl;
    // std::cout << "UPDATE + FINISH = " << CommandTypeEC::UPDATE + CommandTypeEC::FINISH << std::endl; // compile error
    std::cout << std::endl;
}

void convert_to_int() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "CT_FINISH + 3 = " << CT_FINISH + 3 << std::endl;
    std::cout << "CommandTypeEC::FINISH + 3 = " << static_cast<int>(CommandTypeEC::FINISH) + 3 << std::endl;
    std::cout << std::endl;
}

enum OperationE : uint8_t {
    O_START,
    O_STOP
};

enum class OperationEC : uint8_t {
    START,
    STOP
};

void enum_with_basic_type() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "underlying type of OperationE = "
        << typeid(std::underlying_type<OperationE>::type).name() << std::endl;
    std::cout << "underlying type of OperationEC = "
        << typeid(std::underlying_type<OperationEC>::type).name() << std::endl;
    std::cout << std::endl;

    std::cout << std::boolalpha;
    std::cout << "underlying type of OperationE is uint8_t ? "
        << std::is_same<std::underlying_type<OperationE>::type, uint8_t>::value << std::endl;
    std::cout << "underlying type of OperationEC is uint8_t ? "
        << std::is_same<std::underlying_type<OperationEC>::type, uint8_t>::value << std::endl;
    std::cout << std::endl;
}

enum ColorE {
    CYAN = 1,   // 1
    MAGENTA,    // 2
    YELLOW,     // 3
    BLACK = 0  // 0
};

enum class ColorEC {
    CYAN = 1,  // 1
    MAGENTA,   // 2
    YELLOW,    // 3
    BLACK = 0  // 0
};

void enum_values() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "CYAN = " << CYAN << std::endl;
    std::cout << "MAGENTA = " << MAGENTA << std::endl;
    std::cout << "YELLOW = " << YELLOW << std::endl;
    std::cout << "BLACK = " << BLACK << std::endl;
    std::cout << std::endl;

    std::cout << "CYAN = " << static_cast<int>(ColorEC::CYAN) << std::endl;
    std::cout << "MAGENTA = " << static_cast<int>(ColorEC::MAGENTA) << std::endl;
    std::cout << "YELLOW = " << static_cast<int>(ColorEC::YELLOW) << std::endl;
    std::cout << "BLACK = " << static_cast<int>(ColorEC::BLACK) << std::endl;
    std::cout << std::endl;
}

enum ChecksFlag : uint8_t {
    CF_NONE = (0 << 0), // 0
    CF_TIME = (1 << 0), // 1
    CF_KEYS = (1 << 1), // 2
    CF_USER = (1 << 2), // 4
    CF_CERT = (1 << 3), // 8
    CF_ALL = CF_TIME | CF_KEYS | CF_USER | CF_CERT // 15
};

void bit_mask_enum() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "CF_NONE = " << +CF_NONE << ", bit_mask = " << std::bitset<8>(CF_NONE) << std::endl;
    std::cout << "CF_TIME = " << +CF_TIME << ", bit_mask = " << std::bitset<8>(CF_TIME) << std::endl;
    std::cout << "CF_KEYS = " << +CF_KEYS << ", bit_mask = " << std::bitset<8>(CF_KEYS) << std::endl;
    std::cout << "CF_USER = " << +CF_USER << ", bit_mask = " << std::bitset<8>(CF_USER) << std::endl;
    std::cout << "CF_CERT = " << +CF_CERT << ", bit_mask = " << std::bitset<8>(CF_CERT) << std::endl;
    std::cout << "CF_ALL = " << +CF_ALL << ", bit_mask = " << std::bitset<8>(CF_ALL) << std::endl;
    std::cout << std::endl;

    auto result = CF_TIME | CF_USER; // int (implicit cast)
    std::cout << "CF_TIME | CF_USER = " << result << ", bit_mask = " << std::bitset<8>(result) << std::endl;
    std::cout << std::endl;
}

enum class NetworkCommand {
    START = 1,
    STOP = 2,
    PAUSE = 1,  // опасный дубликат!
    RESUME = 3
};

void danger_enum_example() {
    std::cout << __func__ << ':' << std::endl;
    int received_data = 1;
    NetworkCommand cmd = static_cast<NetworkCommand>(received_data);

    std::cout << "Получена команда: " << static_cast<int>(cmd) << std::endl; // 1
    // Невозможно определить настоящую команду!
    if (cmd == NetworkCommand::START) { // условиe выполнится!
        std::cout << "Запускаем процесс..." << std::endl;
    }

    if (cmd == NetworkCommand::PAUSE) { // условиe выполнится!
        std::cout << "Приостанавливаем процесс..." << std::endl;

    }
    std::cout << "cmd == START: " << (cmd == NetworkCommand::START) <<  std::endl;   // true
    std::cout << "cmd == PAUSE: " << (cmd == NetworkCommand::PAUSE) <<  std::endl;   // true
    std::cout << "START == PAUSE: " << (NetworkCommand::START == NetworkCommand::PAUSE) <<  std::endl; // true!
    std::cout << std::endl;
}

enum ColorWide {
    CW_CYAN = 1,   // 1
    CW_MAGENTA,    // 2
    CW_YELLOW,     // 3
    CW_BLACK = 0,  // 0
    CW_WHITE       // 1
};

void unexpected_danger_enum_example() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "CYAN = " << CW_CYAN << std::endl;
    std::cout << "MAGENTA = " << CW_MAGENTA << std::endl;
    std::cout << "YELLOW = " << CW_YELLOW << std::endl;
    std::cout << "BLACK = " << CW_BLACK << std::endl;
    std::cout << "WHITE = " << CW_WHITE << std::endl;
    std::cout << std::boolalpha << "WHITE == CYAN ? " << (CW_CYAN == CW_WHITE) << std::endl;
    std::cout << std::noboolalpha << std::endl;
}

enum class CommandTypeCount {
    INIT,
    UPDATE,
    FINISH,
    COUNT
};

void enum_with_count() {
    std::cout << __func__ << ':' << std::endl;
    for (int i = 0; i < static_cast<int>(CommandTypeCount::COUNT); ++i) {
        switch (static_cast<CommandTypeCount>(i)) {
            case CommandTypeCount::INIT: std::cout << "INIT" << std::endl; break;
            case CommandTypeCount::UPDATE: std::cout << "UPDATE" << std::endl; break;
            case CommandTypeCount::FINISH: std::cout << "FINISH" << std::endl; break;
            case CommandTypeCount::COUNT: std::cout << "COUNT" << std::endl; break;
            default: std::cout << "unknown enum" << std::endl; break;
        }
    }
    std::cout << std::endl;
}

enum class ABC {
    A = 1,
    B = 3,
    C = 5
};

void convert_to_unknow_enum_class_value() {
    std::cout << __func__ << ':' << std::endl;
    auto result = static_cast<ABC>(2);
    std::cout << "type of result: " << typeid(result).name() << std::endl;
    switch (result) {
        case ABC::A: std::cout << "A" << std::endl; break;
        case ABC::B: std::cout << "B" << std::endl; break;
        case ABC::C: std::cout << "C" << std::endl; break;
        default: std::cout << "unknown enum with value = " << static_cast<int>(result) << std::endl; break;
    }
    std::cout << std::endl;
}



int main() {
    unscoped_enum();
    scoped_enum();
    underlying_type_enum();
    arithmetic_operations();
    convert_to_int();
    enum_with_basic_type();
    enum_values();
    bit_mask_enum();
    danger_enum_example();
    unexpected_danger_enum_example();
    enum_with_count();
    convert_to_unknow_enum_class_value();
    return 0;
}