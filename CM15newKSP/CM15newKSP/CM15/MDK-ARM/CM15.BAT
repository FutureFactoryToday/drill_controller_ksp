SET PATH=C:\Keil_v5\ARM\ARMCLANG\Bin;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\dotnet\;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\170\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\150\Tools\Binn\;C:\Program Files\Microsoft SQL Server\150\Tools\Binn\;C:\Program Files\Microsoft SQL Server\150\DTS\Binn\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Git\cmd;C:\Users\Andrey.DESKTOP-GBJSSRT\AppData\Local\Microsoft\WindowsApps;C:\Users\Andrey.DESKTOP-GBJSSRT\AppData\Local\gitkraken\bin
SET CPU_TYPE=STM32F103RC
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=CM15
SET CPU_CLOCK=0x007A1200
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\startup_stm32f103xe._ac"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\main.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\gpio.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\spi.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\stm32f1xx_it.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\ssd1322_api.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\ssd1322_gfx.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\ssd1322_hw_driver.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\fonts.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\st7565.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\stm32f1xx_ll_gpio.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\stm32f1xx_ll_spi.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\stm32f1xx_ll_dma.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\stm32f1xx_ll_rcc.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\stm32f1xx_ll_utils.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\stm32f1xx_ll_exti.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\stm32f1xx_ll_pwr.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cm15\system_stm32f1xx.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmLink" --Via "CM15\CM15.lnp"
"C:\Keil_v5\ARM\ARMCLANG\Bin\fromelf.exe" "CM15\CM15.axf" --i32combined --output "CM15\CM15.hex"
