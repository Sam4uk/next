/**
 * @file IntelHex.hpp
 * @author Sam4uk (you@domain.com)
 * @brief IntelHexFile
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) Sam4uk 2023
 *
 */

#ifndef INTEL_HEX
#define INTEL_HEX

#include <cstdint>
#include <ostream>
/**
 * @brief Типи записів які пітримують інтелхекс файли
 */
enum DATA_TYPE {
  RECORD_DAT = 0x00,  // < Data Record
  RECORD_EOF,         // < End of File Record
  RECORD_ESA,         // < Extended Segment Address Record
  RECORD_SSA,         // < Start Segment Address Record
  RECORD_ELA,         // < Extended Linear Address Record
  RECORD_SLA,         // < Start Linear Address Record
};

class IHEX_RECORD {
 public:
  /**
   * @brief Construct a new ihex line object
   */
  IHEX_RECORD() = default;
  IHEX_RECORD(const uint16_t addr, const char* data, const uint8_t size,
              DATA_TYPE rectype)
      : _offset{addr}, _data{data}, _reclen{size}, _rectype{rectype} {}

 private:
  friend std::ostream& operator<<(std::ostream& os, const IHEX_RECORD ih);
  // /**
  //  * @brief Construct a new ihex line object
  //  *
  //  * @param addr[in] Адреса початку запису даних
  //  * @param data[in] Дані які записуються
  //  * @param type[in] Тип даних що записуються
  //  */
  // IHEX_line(uint16_t addr, std::string data,
  //           DATA_TYPE type = (DATA_TYPE::RECORD_DAT))
  //     : _offset{addr}, _data{data}, record_type{type} {};

  static const int8_t                 //
      _marker = ':',                  //
      _10 = 0x0A,                     //
      Char0Offset = 0x30,             //
      CharAoffset = Char0Offset + 7;  //
  uint8_t                             //
      _reclen = 0x00;                 //
  uint16_t                            //
      _offset = 0x0000;               //
  DATA_TYPE                           //
      _rectype = RECORD_DAT;          //
  const char*                         //
      _data;                          //
  inline int8_t                       //
  checksum() const {                  //
    int8_t result{};
    result += static_cast<int8_t>(recordLen());       //
    result += static_cast<int8_t>(getoffset() >> 8);  //
    result += static_cast<int8_t>(getoffset() & 0xFF);
    result += static_cast<int8_t>(getRecordType());
    {
      uint8_t index = 0;
      while (index < recordLen()) result += static_cast<int8_t>(_data[index++]);
    }
    return (0x100U - result);
  }
  inline uint8_t       //
  recordLen() const {  //
    return ((nullptr == _data) ? (0x00) : (_reclen));
  }
  inline uint8_t           //
  getRecordType() const {  //
    return ((0 == recordLen()) ? (DATA_TYPE::RECORD_EOF) : (_rectype));
  }
  inline uint16_t      //
  getoffset() const {  //
    return ((0 == recordLen()) ? (0x0000) : (_offset));
  }
  std::string                                            //
  nibble(uint8_t value) const {                          //
    const uint8_t                                        //
        hi_nibble = static_cast<uint8_t>(value >> 4),    //
        lo_nibble = static_cast<uint8_t>(value & 0x0F);  //
    std::string                                          //
        result{static_cast<char>(
            (hi_nibble >= _10) ? (hi_nibble + CharAoffset)
                               : (hi_nibble + Char0Offset))};  //< HIGH NIBBLE

    return result += static_cast<char>(
               (lo_nibble >= _10) ? (lo_nibble + CharAoffset)
                                  : (lo_nibble + Char0Offset));  ///< LOW NIBBLE
  }
};

std::ostream& operator<<(std::ostream& os, const IHEX_RECORD ih) {
  os << ih._marker                                                       //
     << ih.nibble(ih.recordLen())                                        //
     << ih.nibble(static_cast<char>((ih.getoffset() & 0xFF00) >> 0x08))  //
     << ih.nibble(static_cast<char>(ih.getoffset() & 0x00FF))
     << ih.nibble(static_cast<char>(ih.getRecordType()));  //
  {
    uint8_t         //
        index = 0;  //
    while (index < ih.recordLen())
      os << ih.nibble(static_cast<int8_t>(ih._data[index++]));
  }
  os << ih.nibble(static_cast<uint8_t>(ih.checksum())) << std::endl;
  // ":00000001FF";
  return os;
};
class IHEX_CLEAR {
 public:
  IHEX_CLEAR() = default;
  IHEX_CLEAR(uint16_t StartOffset, uint16_t MemmorySize, uint8_t RecordLength,
             DATA_TYPE RecordType = DATA_TYPE::RECORD_DAT,
             uint8_t CellFill = 0xFF)
      : _StartOffset{StartOffset},
        _MemmorySize{MemmorySize},
        _RecordLength{RecordLength},
        _RecordType{RecordType},
        _CellFill{CellFill} {}
  friend std::ostream& operator<<(std::ostream& os, const IHEX_CLEAR ih);

 private:
  uint16_t _StartOffset = 0x0000;
  uint16_t _MemmorySize = 0x0000;
  uint8_t _RecordLength = 0x00;
  DATA_TYPE _RecordType = DATA_TYPE::RECORD_DAT;
  uint8_t _CellFill = 0xFF;
};

std::ostream& operator<<(std::ostream& os, const IHEX_CLEAR ih) {
  std::string        //
      MemoryDump{};  ///< Дамп пам'яті
  for (size_t MemoryCell{0}; MemoryCell <= ih._MemmorySize; MemoryCell++)
    MemoryDump += static_cast<int8_t>(ih._CellFill);
  uint16_t RecordsCount = 0,  ///< Кількість
      Offset,                 /// < Відносиний офсет
      LentToEnd;
  do {
    Offset =
        RecordsCount * ih._RecordLength;  // рахуємо офсет для кожного запису
    LentToEnd = MemoryDump.length() - Offset;
    os << IHEX_RECORD(ih._StartOffset + Offset, MemoryDump.c_str() + Offset,
                      (LentToEnd > ih._RecordLength)  // перівярємо залишок
                                                      // якщо ще вдосталь
                          ? (ih._RecordLength)  // генеруємо повний рядок
                          : (LentToEnd),  // інакше залишковий
                      ih._RecordType      // Тип запису
    );
    RecordsCount++;  // переходимо до наступного
    if (LentToEnd <= ih._RecordLength and RecordsCount > 1) os << IHEX_RECORD();
    // if (0 == ih._RecordLength) break;
  } while (LentToEnd > ih._RecordLength);  // повтороємо допоки повні рядки
  return os;
}

#endif
