#ifndef SWAY_PLATFORM_UNIX_OIS_OISPREREQS_H
#define SWAY_PLATFORM_UNIX_OIS_OISPREREQS_H

#include "../../../types.h"
#include "../../../defines.h"
#include "../../../memory/safedeletemacros.h"

#include "../../../foundation/object.h"
#include "../../../foundation/declareobjectmacros.h"
#include "../../../foundation/context.h"

#include <boost/function.hpp> // boost::function
#include <boost/bind.hpp> // boost::bind

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <string> // std::string
#include <map> // std::map, std::multimap

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

struct KeyMapping;
struct InputEventKeyPress;
struct InputEventKeyRelease;

class InputManager;
class KeyboardListener;
class Keyboard;
class Mouse;

typedef std::multimap<u32, std::string> DeviceList;
typedef std::multimap<std::string, std::string> ParamList;

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_OISPREREQS_H