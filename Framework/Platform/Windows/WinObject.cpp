/* Copyright © 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of LupusFramwork.
 *
 * LupusFramwork is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LupusFramwork is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LupusFramwork.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "..\..\Types.hpp"

#ifdef LUPUS_WINDOWS_PLATFORM
#include <Windows.h>
#include "..\..\String.hpp"
#include "..\..\Exception.hpp"

namespace Lupus {
	Object::Object()
	{
		_mutex = CreateMutex(NULL, FALSE, NULL);

		if (!_mutex) {
			throw SystemException("couldn't create mutex object");
		}
	}

	Object::~Object()
	{
		if (!CloseHandle(_mutex)) {
			throw SystemException("couldn't close mutex");
		}
	}

	void Object::Lock()
	{
		switch (WaitForSingleObject(_mutex, INFINITE)) {
		case WAIT_OBJECT_0:
			return;
		case WAIT_FAILED:
		case WAIT_TIMEOUT:
		case WAIT_ABANDONED:
			throw SystemException("error while locking this object");
		}
	}

	bool Object::TryLock()
	{
		switch (WaitForSingleObject(_mutex, 0)) {
		case WAIT_OBJECT_0:
			return true;
		case WAIT_TIMEOUT:
		case WAIT_FAILED:
			return false;
		case WAIT_ABANDONED:
			throw SystemException("thread got ownership of an abondoned mutex");
		}

		return false;
	}
	
	void Object::Unlock()
	{
		if (!ReleaseMutex(_mutex)) {
			throw SystemException("error while ownership of mutex was released");
		}
	}
}

#endif
