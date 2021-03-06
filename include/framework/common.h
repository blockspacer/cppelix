#pragma once

namespace Cppelix {
    template<typename INTERFACE_TYPENAME>
    [[nodiscard]] constexpr auto typeName() {
        constexpr std::string_view result = __PRETTY_FUNCTION__;
        constexpr std::string_view templateStr = "INTERFACE_TYPENAME = ";

        constexpr size_t bpos = result.find(templateStr) + templateStr.size(); //find begin pos after INTERFACE_TYPENAME = entry
        if constexpr (result.find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_:") == std::string_view::npos) {
            constexpr size_t len = result.length() - bpos;

            static_assert(!result.substr(bpos, len).empty(), "Cannot infer type name in function call");

            return result.substr(bpos, len);
        } else {
            constexpr size_t len = result.substr(bpos).find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_:");

            static_assert(!result.substr(bpos, len).empty(), "Cannot infer type name in function call");

            return result.substr(bpos, len);
        }
    }

    struct InterfaceVersion {
        constexpr InterfaceVersion(uint64_t _major, uint64_t _minor, uint64_t _patch) noexcept : major(_major), minor(_minor), patch(_patch) {}
        constexpr InterfaceVersion(const InterfaceVersion &other) noexcept = default;
        constexpr InterfaceVersion(InterfaceVersion &&other) noexcept = default;
        constexpr InterfaceVersion& operator=(const InterfaceVersion &other) noexcept = default;
        constexpr InterfaceVersion& operator=(InterfaceVersion &&other) noexcept = default;
        constexpr std::strong_ordering operator<=>(const InterfaceVersion&) const noexcept = default;

        uint64_t major;
        uint64_t minor;
        uint64_t patch;
    };

    template <class T, class U>
    concept Derived = std::is_base_of<U, T>::value;

    // TODO BundleInterface on actual interface fails due to pure virtual functions or something
//    template <class T>
//    concept BundleInterface = requires(T bundleInterface) {
//        { bundleInterface.version() } -> std::same_as<InterfaceVersion>;
//    };
}