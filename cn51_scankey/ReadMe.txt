========================================================================
    WIN32 APPLICATION : cn51_scankey Project Overview
========================================================================

background application that will watch for named events and then fires a key

The tool watches for the renamed barcode scanner events: 
DeltaLeftScan1 and StateLeftScan1 (see registry arguments)

If the events are fired by the barocde scanner button, the tool will issue
a KeyDown and KeyUp message with the value defined by 'virtual key'.

If 'fire scan' is set not 0, the original events are fired in the way
the Datacollection engine is waiting for. So the scanner will be fired
as if the original event names are in place.

========================================================================
configuration:

First you must rename the original events of the scan button. These are 
located in the registry, for example at 
HKEY_LOCAL_MACHINE\Drivers\HID\ClientDrivers\ITCKeyboard\Layout\CN51-Numeric\0001\Events\Delta\Event1
	and
HKEY_LOCAL_MACHINE\Drivers\HID\ClientDrivers\ITCKeyboard\Layout\CN51-Numeric\0001\Events\State\Event1
The original values of "StateLeftScan" and "DeltaLeftScan" must be renamed to, for example
to "StateLeftScan1" and "DeltaLeftScan1". Then use the new names to configure the registry.

The 'virtual key' is the byte key value as defined in winuser.h and winuserm.h. For example, the 
windows key is named VK_LWIN and has byte value 0x5B. 
This value will be used to simulate a key down and up event.

If 'fire scan' is active (equal 1), then the original events are fired. The names are hardcoded as
"StateLeftScan" and "DeltaLeftScan". Normally the barcode scanner will be triggered as the trigger
button has been pressed. If 'fire scan' is 0, the original events are not fired.

========================================================================
REGEDIT4

[HKEY_LOCAL_MACHINE\Software\cn51_scankey]
"fire scan"=hex:\
      01
"virtual key"=hex:\
      5B
"DeltaLeftEvent"="DeltaLeftScan1"
"StateLeftEvent"="StateLeftScan1"



/////////////////////////////////////////////////////////////////////////////s