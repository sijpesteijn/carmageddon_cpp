/*
 * base64.h
 *
 *  Created on: 22 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_UTIL_BASE64_H_
#define SRC_UTIL_BASE64_H_

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);



#endif /* SRC_UTIL_BASE64_H_ */
