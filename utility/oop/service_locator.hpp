// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015 - 2016, Individual contributors, see AUTHORS file.	|
	| 									|
	| This program is free software: you can redistribute it and/or modify	|
	| it under the terms of the GNU General Public License as published by	|
	| the Free Software Foundation, either version 2 of the License, or	|
	| (at your option) any later version.					|
	|									|
	| This program is distributed in the hope that it will be useful,	|
	| but WITHOUT ANY WARRANTY; without even the implied warranty of	|
	| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the		|
	| GNU General Public License for more details.				|
	|									|
	| You should have received a copy of the GNU General Public License	|
	| along with this program.  If not, see <http://www.gnu.org/licenses/>. |
	|									|
	+-----------------------------------------------------------------------+	*/



#ifndef __YAHAL_UTILITY_OOP_SERVICE_LOCATOR_HPP_INCLUDED__
#define __YAHAL_UTILITY_OOP_SERVICE_LOCATOR_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace oop{
//	template<typename T_SERVICE, typename T_EMPTY_SERVICE> class ServiceLocator;
	template<typename T_SERVICE> class ServiceLocator;
	template<typename T_SERVICE, typename T_EMPTY_SERVICE> class GlobalServiceLocator;
}}}



/***********************************************************************************************//**
 *
 **************************************************************************************************/
/*template<typename T_SERVICE, typename T_EMPTY_SERVICE>
class yahal::utility::oop::ServiceLocator
{
public:
				ServiceLocator(T_SERVICE& service) : service_(&service) {}
				ServiceLocator(void) : service_(&empty_service_)		{}

	inline void	 	set(T_SERVICE& new_service)	{ service_ = &new_service; }
	inline void		disable(void)			{ service_ = & empty_service_; }
	inline T_SERVICE&	get(void)		 	{ return *service_; }

private:
	T_SERVICE*		service_;
	static T_EMPTY_SERVICE	empty_service_;
};

// Static instance of empty_service_
template<typename T_SERVICE, typename T_EMPTY_SERVICE> T_EMPTY_SERVICE yahal::utility::oop::ServiceLocator<T_SERVICE, T_EMPTY_SERVICE>::empty_service_;
*/

template<typename T_SERVICE>
class yahal::utility::oop::ServiceLocator
{
public:
				ServiceLocator(T_SERVICE& service) : service_(&service) {}

	inline void	 	set(T_SERVICE& new_service)	{ service_ = &new_service; }
	inline T_SERVICE&	get(void) const		 	{ return *service_; }

private:
	T_SERVICE*		service_;
};



/***********************************************************************************************//**
 *
 **************************************************************************************************/
template<typename T_SERVICE, typename T_EMPTY_SERVICE>
class yahal::utility::oop::GlobalServiceLocator
{
private:
				GlobalServiceLocator(void)	{}

public:
	inline static void	set(T_SERVICE& new_service)	{ service_ = &new_service; }
	inline static void	disable(void)			{ service_ = & empty_service_; }
	inline T_SERVICE&	get(void)		 	{ return *service_; }

private:
	static T_SERVICE*	service_;
	static T_EMPTY_SERVICE	empty_service_;
};

/// Static instance of empty_service_
template<typename T_SERVICE, typename T_EMPTY_SERVICE> T_EMPTY_SERVICE yahal::utility::oop::GlobalServiceLocator<T_SERVICE, T_EMPTY_SERVICE>::empty_service_;

/// Static instance of service_ initialized to empty_service_
template<typename T_SERVICE, typename T_EMPTY_SERVICE> T_SERVICE* yahal::utility::oop::GlobalServiceLocator<T_SERVICE, T_EMPTY_SERVICE>::service_\
	= &yahal::utility::oop::GlobalServiceLocator<T_SERVICE, T_EMPTY_SERVICE>::empty_service_;





/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_SERVICE_LOCATOR_HPP_INCLUDED__
