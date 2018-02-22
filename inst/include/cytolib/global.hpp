/*
 * global.hpp
 *
 *  Created on: Mar 31, 2014
 *      Author: wjiang2
 */

#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#define GATING_SET_LEVEL 1
#define GATING_HIERARCHY_LEVEL 2
#define POPULATION_LEVEL 3
#define GATE_LEVEL 4


#ifdef ROUT
#include <R_ext/Print.h>
#endif

#include <iostream>
#include <string>
#include <memory>
#include <ctype.h>
#include <vector>

#include <armadillo>
using namespace arma;

using namespace std;
extern unsigned short g_loglevel;// debug print is turned off by default
extern bool my_throw_on_error;//can be toggle off to get a partially parsed gating tree for debugging purpose
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
namespace cytolib
{
	#define CYTOLIB_INIT() \
			bool my_throw_on_error = true;\
			unsigned short g_loglevel = 0;\

	inline void PRINT(string a){
	#ifdef ROUT
	 Rprintf(a.c_str());
	#else
	 cout << a;
	#endif

	}
	inline void PRINT(const char * a){
	#ifdef ROUT
	 Rprintf(a);
	#else
	 cout << a;
	#endif

	}



	const int bsti = 1;  // Byte swap test integer
	#define is_host_big_endian() ( (*(char*)&bsti) == 0 )

	typedef double EVENT_DATA_TYPE;
	typedef arma::Mat<EVENT_DATA_TYPE> EVENT_DATA_VEC;

	#define PRT true

	/**
	 * Generate time stamp as string
	 * @return
	 */
	inline string generate_timestamp()
	{
		time_t rawtime;
		time(&rawtime);
		char out[13];
		strftime(out, 13, "%y%m%d%H%M%S", localtime(&rawtime));
		out[12] ='\0';
		return string(out);
	}
	/**
	 * Generate uniquely identifiable id (pseudo guid)
	 * @return
	 */
	inline string generate_guid(int len)
	{
		srand (time(NULL));
		char s[len+1];
		static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		s[0] = alphanum[rand() % (sizeof(alphanum) - 11) + 10];
		for (int i = 1; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		s[len] = '\0';
		return string(s);
	}
	inline string path_dir_name(const string & full_path)
	{
//		//TODO:handle windows path
//		size_t i_last_slash = full_path.find_last_of('/');
//		return full_path.substr(0,i_last_slash);
		return fs::path(full_path).parent_path().string();
	}
	inline string path_base_name(const string & full_path)
	{
//		//TODO:handle windows path
//		size_t i_last_slash = full_path.find_last_of('/');
//		return full_path.substr(i_last_slash);
		return fs::path(full_path).filename().string();
	}


};

#endif /* GLOBAL_HPP_ */
