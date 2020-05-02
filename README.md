# gosdk
gosdk is a CS:GO SDK that is currently in development, written in C++17 standard, that empowers users to write CS:GO cheats.

# information
The formatting method for gosdk is Clang Format, using the Linux Kernel config. Include Guards are handled by using globals for every filter.

# contribution guidelines
To contribute to gosdk, you need to always adapt your code to the clang format, by re-pasting it into the code file (if you're using Visual Studio, as it's supported by default), and you are also required to specify if your addition was ran through tests to notice if there's any crash occouring due to it. This applies to every commit you plan on doing that it's dirrectly related to the source code.

# features
gosdk currently comes with the IConsole interface, ISurface interface and IInputSystem interface, a VMT hooking class, sv_cheats bypass (hooked), grenade trajectory (convar, hooked), lock cursor [currently while Insert is hold] (hooked), a console with logging, basic error handling, math utilities, various easing functions and utilities which include a color handler and a config system, memory functions many others. These are not final and are to be updated.
