#pragma once
#include <array>
#include <optional>
#include <string>
#include <vector>


namespace anl
{
   class Ip4Addr
   {
      Ip4Addr() = default;
   public:
      using ipv4ad = std::array<uint8_t, 4>;


      ~Ip4Addr() = default;
      Ip4Addr(const Ip4Addr& other) = default;
      Ip4Addr(Ip4Addr&& other) noexcept = default;
      Ip4Addr& operator=(const Ip4Addr& other) = default;
      Ip4Addr& operator=(Ip4Addr&& other) noexcept = default;


      std::string toString() const;

      uint64_t toUint64() const;


      static std::optional<Ip4Addr> fromString(const char* ip);
      static Ip4Addr fromULong(uint64_t address);
      static Ip4Addr any();
      static bool isAddressIsValid(const char* ip);

      ipv4ad a;
   private:
   };


}
