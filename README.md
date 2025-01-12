# MJUADS Autosplitter Utility
A utility to configure autosplitting for Monster Jam: Urban Assault DS

## How does it work?
- [ShootMe's DeSmuME Autosplitter component](https://github.com/ShootMe/LiveSplit.DeSmuME) works with LiveSplit and DeSmuME's memory to accurately split based on checking game addresses. However, this is only possible by configuring it to your layout, which is both tedious and can go wrong easily. This utility automates that process and (hopefully) works 100% of the time!
- This autosplits upon pressing 'A' on the first track and then continues to split on the completion of each race.

## Disclaimers
- Resetting is manual.
- Make sure to quit the track and end up on the track menu before resetting.
- This autosplitter only supports DeSmuME 0.9.11.
- v0.2-alpha only has support for the Speedster% category.
- Since this project is currently not fully developed, please copy your LiveSplit layout file somewhere else before using the program, because the program directly modifies your layout file.
- Change your split file to start at 0.20 seconds for the timing to be as accurate as possible with manual retiming.

## Usage
- Download both the LiveSplit.DeSmuME.dll and MJUADS_Autosplitter_Utility_(version).exe files from [Releases](https://github.com/skyywaffle/MJUADS_Autosplitter_Utility/releases).
- Place LiveSplit.DeSmuME.dll in your LiveSplit/Components directory.
- Launch MJUADS_Autosplitter_Utility.exe and configure according to game version and category!
- Your layout file should then be all ready for autosplitting.

## Contributing
This software is made using wxWidgets 3.2.6. If you have any suggestions or want to notify me of bugs/problems, you can contact me on Discord (@skyywaffle).
