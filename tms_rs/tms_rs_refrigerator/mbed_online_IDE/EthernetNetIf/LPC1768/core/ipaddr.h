
/*
Copyright (c) 2010 Donatien Garnier (donatiengar [at] gmail [dot] com)
<<<<<<< HEAD

=======
 
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
<<<<<<< HEAD

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

=======
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
 
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef IPADDR_H
#define IPADDR_H

#include "netCfg.h"
#if NET_LWIP_STACK
typedef struct ip_addr ip_addr_t;
#endif

#include "stdint.h"

<<<<<<< HEAD
/// IP Address container
/**
This class is a container for an IPv4 address.
*/
class IpAddr  // Basically a C++ frontend to ip_addr_t
{
public:
#if NET_LWIP_STACK
  IpAddr(ip_addr_t* pIp);
#endif

  /// Initializes IP address with provided values
  IpAddr(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3);

  /// Initializes IP address with null values
  IpAddr();

#if NET_LWIP_STACK
  ip_addr_t getStruct() const;
#endif

  /// Returns IP address byte #
  uint8_t operator[](unsigned int i) const;

  /// Compares too addresses
=======
///IP Address container
/**
This class is a container for an IPv4 address.
*/
class IpAddr //Basically a C++ frontend to ip_addr_t
{
public:
  #if NET_LWIP_STACK
  IpAddr(ip_addr_t* pIp);
  #endif
  
  ///Initializes IP address with provided values
  IpAddr(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3);
  
  ///Initializes IP address with null values 
  IpAddr();

  #if NET_LWIP_STACK
  ip_addr_t getStruct() const;
  #endif
  
  ///Returns IP address byte #
  uint8_t operator[](unsigned int i) const;
  
  ///Compares too addresses
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
  /**
  @return true if the two addresses are equal
  */
  bool isEq(const IpAddr& b) const;
<<<<<<< HEAD

  /// Compares too addresses
=======
  
  ///Compares too addresses
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
  /**
  @return true if the two addresses are equal
  */
  bool operator==(const IpAddr& b) const;
<<<<<<< HEAD

  /// Compares too addresses
  /**
  @return true if the two addresses are different
  */
  bool operator!=(const IpAddr& b) const;

  /// Checks whether the address is null
=======
 
  ///Compares too addresses
  /**
  @return true if the two addresses are different
  */ 
  bool operator!=(const IpAddr& b) const;
  
  ///Checks whether the address is null
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
  /**
  @return true if the address is null
  */
  bool isNull() const;
<<<<<<< HEAD

  /// Checks whether the address is a broadcast address
=======
  
  ///Checks whether the address is a broadcast address
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
  /**
  @return true if the address is a broadcast address
  */
  bool isBroadcast() const;

<<<<<<< HEAD
  /// Checks whether the address is a multicast address
=======
  ///Checks whether the address is a multicast address
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
  /**
  @return true if the address is a multicast address
  */
  bool isMulticast() const;
<<<<<<< HEAD

=======
  
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
private:
  uint8_t m_ip[4];
};

#endif
