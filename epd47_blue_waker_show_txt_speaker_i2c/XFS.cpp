#include "XFS.h"
#include <Wire.h>

#define XFS_WIRE Wire

#define XFS_DataHead (uint8_t)0xFD

XFS5152CE::XFS5152CE(EncodingFormat_Type encodingFormat)
{
  DataPack.DataHead = XFS_DataHead;
  DataPack.Length_HH = 0x00;
  DataPack.Length_LL = 0x00;

  DataPack.Commond = 0x00;
  DataPack.EncodingFormat = encodingFormat;

  ChipStatus = 0x00;
}



String XFS5152CE::tohex_string(const uint8_t * cmd_buff, int sourceLen)
{
  String ret = "";
  for (int i = 0; i < sourceLen; i ++)
  {
    if (i == 0)
      ret = "0x" + tohex(cmd_buff[i]) ;
    else
      ret = ret + "," + "0x" + tohex(cmd_buff[i]) ;
  }
  return ret;
}

//十进制转十六进制
String XFS5152CE::tohex(uint8_t n)
{
  if (n == 0) {
    return "00"; //n为0
  }
  String result = "";
  char _16[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
  };
  int radix = 16;
  while (n) {
    int i = n % radix;          // 余数
    result = _16[i] + result;   // 将余数对应的十六进制数字加入结果
    n /= radix;                 // 除以16获得商，最为下一轮的被除数
  }
  if (result.length() < 2) {
    result = '0' + result; //不足两位补零
  }
  return result;
}

//设计最多处理100个汉字
//utf8 汉字3个字符 字母数字等1个字符
//utf16Str 至少要能存100汉字
//size_char 返回有几个字
void XFS5152CE::utf8ToUtf16String(String gUtf8ZhString, size_t &size_char)
{
  char * utf8Str;
  char tmp_buf[300];
  uint32_t gUtf32ZhString[100];

  uint16_t * utf16Str;
  utf16Str = utf16_buff;

  // size_t size_byte;     //占多少个字节
  size_t size_byte = gUtf8ZhString.length();
  //utf8的字符串转成字符数组 tmp_buf
  gUtf8ZhString.toCharArray(tmp_buf, size_byte + 1);
  //Serial.println("utf8字节长度:" + String(size_byte));
  utf8GetLengthAndSize(tmp_buf, size_char, size_byte);
  // Serial.println("utf8字符长度:" + String(size_char));
  // Serial.println("utf8字节长度:" + String(size_byte));
  //调用库函数，将tmp_buf字符串数组转成 32位utf格式
  utf8ToUtf32String(gUtf32ZhString, tmp_buf, size_byte);
  //每个字固定4个字节，所以剩以4
  //  Serial.println( tohex_string((const uint8_t *)gUtf32ZhString, size_char * 4));
  //32位UTF格式转成16位格式
  utf32ToUtf16String(gUtf32ZhString, utf16Str, size_char);
  //  Serial.println( tohex_string((const uint8_t *)utf16Str, size_char * 2));
  //return String((const char *)utf16Str);
}


//utf32 转成 utf16的 UNICODE
void XFS5152CE::utf32ToUtf16String( uint32_t *  utf32Str, uint16_t * utf16Str, size_t  strSize)
{
  uint32_t char32;
  uint16_t char16;
  for (int i = 0; i < strSize; i ++)
  {
    char32 = utf32Str[i];
    char16 = char32;
    utf16Str[i] = char16;
  }
}

void XFS5152CE::Begin_with_pin(uint8_t addr, int sda_pin, int scl_pin)
{
  I2C_Addr = addr;
  XFS_WIRE.begin(sda_pin, scl_pin);
}

void XFS5152CE::Begin(uint8_t addr)
{
  I2C_Addr = addr;
  XFS_WIRE.begin();
}

uint8_t XFS5152CE::GetChipStatus()
{
  uint8_t AskState[4] = {0xFD, 0x00, 0x01, 0x21};
  XFS_WIRE.beginTransmission(I2C_Addr);
  XFS_WIRE.write(AskState, 4);
  XFS_WIRE.endTransmission();
  delay(100);
  XFS_WIRE.requestFrom(I2C_Addr, 1);
  while (XFS_WIRE.available())
  {
    ChipStatus = XFS_WIRE.read();
  }
  return ChipStatus;
}


//bool XFS5152CE::IIC_WriteByte(uint8_t data)
bool XFS5152CE::IIC_WriteByte(int data)
{
  Wire.beginTransmission(I2C_Addr);
  Wire.write(data);
  if (Wire.endTransmission() != 0)         //发送结束信号
  {
    delay(10);
    return false;
  }
  delay(10);
  return true;
}

//void XFS5152CE::IIC_WriteBytes(uint8_t* buff, uint32_t size)
//void XFS5152CE::IIC_WriteBytes(const char * buff, uint32_t size)
void XFS5152CE::IIC_WriteBytes(const char * buff, int size)
{
  for (int i = 0; i < size; i++)
  {
    IIC_WriteByte((uint8_t)buff[i]);
  }
}



void XFS5152CE::StartSynthesis(const char* str)
{

  Serial.println("begin StartSynthesis");
  size_t size_char;
  //utf-8字符串转换，必须！
  utf8ToUtf16String(str, size_char);
  utf16_buff[size_char] = '\0';
  Serial.println("size_char=");  
  Serial.println(size_char);
  //后面计算文字长度，传输文字数据均用 utf16_buff, 其长度为 size_char*2
  
  uint16_t size = size_char*2 + 2;
  Serial.println("size=");  
  Serial.println(size);
  DataPack.Length_HH = highByte(size);
  DataPack.Length_LL = lowByte(size);
  
  DataPack.Commond = CMD_StartSynthesis;
  //DataPack.Text = str;
  DataPack.Text = (const char *)utf16_buff;
  Serial.println("DataPack.Text:");
  Serial.println(DataPack.Text);

  //IIC_WriteBytes((uint8_t*)&DataPack,5);
  IIC_WriteBytes((const char *)&DataPack, 5);
  IIC_WriteBytes(DataPack.Text, size_char * 2);
}


void XFS5152CE::StartSynthesis(String str)
{
  StartSynthesis((const char*)str.c_str());
}

void XFS5152CE::SendCommond(CMD_Type cmd)
{
  DataPack.Length_HH = 0x00;
  DataPack.Length_LL = 0x01;
  DataPack.Commond = cmd;

  XFS_WIRE.beginTransmission(I2C_Addr);
  XFS_WIRE.write((uint8_t*)&DataPack, 4);
  XFS_WIRE.endTransmission();
}

void XFS5152CE::StopSynthesis()
{
  SendCommond(CMD_StopSynthesis);
}

void XFS5152CE::PauseSynthesis()
{
  SendCommond(CMD_PauseSynthesis);
}

void XFS5152CE::RecoverySynthesis()
{
  SendCommond(CMD_RecoverySynthesis);
}

void XFS5152CE::TextCtrl(char c, int d)
{
  char str[10];
  if (d != -1)
    sprintf(str, "[%c%d]", c, d);
  else
    sprintf(str, "[%c]", c);
  StartSynthesis(str);
}

void XFS5152CE::SetEncodingFormat(EncodingFormat_Type encodingFormat)
{
  DataPack.EncodingFormat = encodingFormat;
}

void XFS5152CE::SetStyle(Style_Type style)
{
  TextCtrl('f', style);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetLanguage(Language_Type language)
{
  TextCtrl('g', language);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetArticulation(Articulation_Type articulation)
{
  TextCtrl('h', articulation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetSpell(Spell_Type spell)
{
  TextCtrl('i', spell);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetReader(Reader_Type reader)
{
  TextCtrl('m', reader);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetNumberHandle(NumberHandle_Type numberHandle)
{
  TextCtrl('n', numberHandle);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetZeroPronunciation(ZeroPronunciation_Type zeroPronunciation)
{
  TextCtrl('o', zeroPronunciation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}


void XFS5152CE::SetNamePronunciation(NamePronunciation_Type namePronunciation)
{
  TextCtrl('r', namePronunciation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetSpeed(int speed)
{
  speed = constrain(speed, 0, 10);
  TextCtrl('s', speed);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetIntonation(int intonation)
{
  intonation = constrain(intonation, 0, 10);
  TextCtrl('t', intonation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetVolume(int volume)
{
  volume = constrain(volume, 0, 10);
  TextCtrl('v', volume);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetPromptTone(PromptTone_Type promptTone)
{
  TextCtrl('x', promptTone);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetOnePronunciation(OnePronunciation_Type onePronunciation)
{
  TextCtrl('y', onePronunciation);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}

void XFS5152CE::SetRhythm(Rhythm_Type rhythm)
{
  TextCtrl('z', rhythm);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}


void XFS5152CE::SetRestoreDefault()
{
  TextCtrl('d', -1);
  while (GetChipStatus() != ChipStatus_Idle)
  {
    delay(30);
  }
}
