# gosdk
gosdk is a CS:GO SDK that is currently in development, written in C++17 standard, that empowers users to write CS:GO cheats.

# licensing
gosdk is licensed under the GNU v3 license, and according to that, I, Cristei Gabriel-Marian, provide you the code as-is, and give you full freedom over the usage of it, but I will not take responsability for your usage of it.

# information
The formatting method for gosdk is Clang Format, using the Linux Kernel config. Include Guards are handled by using globals for every filter.

# contribution guidelines
To contribute to gosdk, you need to always adapt your code to the clang format, by re-pasting it into the code file (if you're using Visual Studio, as it's supported by default, if you use any other, you'll be required to either install software that handles it if you don't already have the capability of using the 'clang-format' command in your terminal), and you are also required to specify if your addition was ran through tests to notice if there's any crash occouring due to it. This applies to every commit you plan on doing that it's dirrectly related to the source code.

# features
gosdk currently comes with the IConsole interface, ISurface interface, IInputSystem interface, IPanel interface, IBaseClientDLL for Client interface, ClientMode interface, IEngineClient interface, IEntityList interface, IGlobalVars interface, IDebugOverlay interface, a Netvar scanner, a VMT hooking class, sv_cheats bypass (hooked), grenade trajectory (convar, hooked), lock cursor [currently while Insert is hold] (hooked), paint traverse [hooked], create move [hooked], ability to do basic rendering [although there is currently no surface wrapper, you can just use the default surface methods] a console with logging, basic error handling, math utilities, various easing functions and utilities which include a color handler and a config system, memory functions, bunny hop and no duck delay through bitflag easing, Box ESP. These are not final and are to be updated.

# credits
Credits for gosdk go to places where I take inspiration from, and that would be:
- @DucaRii for csgo_modest [his project helped me with the math utilities].
- @ReigN [unknowncheats.me] for their SDK that I have got the VMT Hooking class from, which was a total time saver, despite some nitpickable issues that are not occouring within this project.
- Every supposive contributor.
