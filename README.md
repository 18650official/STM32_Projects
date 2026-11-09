# STM32 学习工程与测试 / STM32 Learning Projects & Tests

本仓库整理了 **江协科技 STM32F103 例程**、个人写的 **Keil MDK 测试用例**，以及一套可用的 **CMake + arm-none-eabi-gcc + OpenOCD + VS Code** 开源工具链配置。

This repository contains the JiangKe STM32F103 examples, personal Keil MDK test projects, and a CMake/open-source toolchain setup for STM32F103.

---

## 目录结构

```text
.
├─ firmware/
│  ├─ JiangKe_Examples/          # 江协科技例程（43 个，保留每个例程的 Library/Start/System）
│  ├─ MDK_Tests/                 # 个人写的 Keil MDK 测试
│  │  ├─ 0.Template/             # 空白工程模板
│  │  ├─ 1.STM32工程测试/        # GPIO / 工程模板测试
│  │  └─ 2.测频率/               # PWM + 输入捕获 + OLED 测频
│  ├─ CMake_Toolchain/           # 开源工具链：CMake + arm-none-eabi-gcc + OpenOCD
│  │  ├─ 1-1 串口收发测试/       # 串口文本协议测试（LED_ON / LED_OFF）
│  │  └─ 移植MDK项目需要替换的文件/
│  ├─ StdPeriph_Lib/             # STM32F10x 标准外设库 V3.5.0
│  └─ .vscode/                   # VS Code 工作区配置（含绝对路径，需按本机修改）
├─ docs/
│  └─ reference/                 # STM32F10x 参考手册、Cortex-M3 指南、数据手册、引脚图
├─ tools/                        # 串口助手、FlyMcu、ST-Link 驱动、CH340 驱动、keilkill
├─ README.md
├─ .gitignore
└─ .gitattributes
```

### 谁负责什么

| 目录 | 内容 |
|---|---|
| `firmware/JiangKe_Examples` | 江协科技（江科大）STM32F103 例程，覆盖 GPIO、OLED、定时器、PWM、输入捕获、编码器、ADC、DMA、USART、I2C、SPI、RTC、低功耗、看门狗、Flash 等。 |
| `firmware/MDK_Tests/1.STM32工程测试` | 最小 Keil 工程测试：使能 GPIOC 时钟、配置 PC13 推挽输出并拉高。 |
| `firmware/MDK_Tests/2.测频率` | PWM（TIM2 PA0）输出，TIM3 PA6 输入捕获测频，OLED 显示频率；用于验证滴速/频率类传感器。 |
| `firmware/CMake_Toolchain/1-1 串口收发测试` | USART1 PA9/PA10，9600 8N1，`@MSG\r\n` 文本协议；收到 `LED_ON`/`LED_OFF` 控制 LED 并回传。 |
| `firmware/CMake_Toolchain/移植MDK项目需要替换的文件` | 把普通 Keil 工程迁移到 CMake 时需要替换/补充的 startup、链接脚本、`.vscode` 等。 |
| `firmware/StdPeriph_Lib` | ST 官方标准外设库 V3.5.0，保留作参考和新建工程使用。 |
| `docs/reference` | 中文/英文参考手册、Cortex-M3 权威指南、编程手册、F103 数据手册、引脚图。 |
| `tools` | 串口助手、FlyMcu、ST-Link 驱动、CH340 驱动、UltraCodingSwitch、`keilkill.bat`。 |

## 快速开始

### 1. Keil MDK

1. 安装 Keil MDK5、STM32F1xx Device Family Pack（DFP）、ST-Link 驱动。
2. 打开任意例程的 `.uvprojx`，例如：
   - `firmware/JiangKe_Examples/3-1 LED闪烁/Project.uvprojx`
   - `firmware/MDK_Tests/2.测频率/Project.uvprojx`
3. Build → Download。
4. 每个例程都自带 `Library/Start/System` 副本，可以独立打开；这是为了保持例程自包含，Git 会对相同文件自动去重存储。

### 2. CMake + arm-none-eabi-gcc + OpenOCD

1. 安装：
   - CMake、Ninja
   - `arm-none-eabi-gcc`（ARM GNU Toolchain）
   - OpenOCD
   - VS Code 扩展：CMake Tools、Cortex-Debug
2. 用 VS Code 打开 `firmware/CMake_Toolchain/1-1 串口收发测试`。
3. 修改本机相关路径：
   - `.vscode/c_cpp_properties.json` 的 `compilerPath`
   - `.vscode/launch.json` 的 `executable`、`configFiles`、`svdFile`
   - 如需修改串口/下载器，改 `launch.json` 里的 OpenOCD 配置。
4. 配置与编译：
   ```powershell
   cmake -B build -G Ninja
   cmake --build build
   ```
   或在 VS Code 中使用 CMake: Configure / Build。
5. 串口测试：USART1 PA9(TX)/PA10(RX)，9600 8N1；发送 `@LED_ON\r\n` 或 `@LED_OFF\r\n`，板子回传 `LED_ON_OK` / `LED_OFF_OK` / `ERROR_COMMAND`。

> 仓库中的 `.vscode/launch.json` 和 `c_cpp_properties.json` 保留了原作者机器上的绝对路径（如 `C:/Users/...`、`D:/Program Files/OpenOCD/...`），换电脑后必须修改。

## 已整理的构建产物

以下内容已排除到仓库外的 `D:\Dev\STM32开发_excluded`（确认无误后可删除）：

- Keil 构建产物：`Objects/`、`Listings/`、`DebugConfig/`、`.o`、`.d`、`.crf`、`.axf`、`.hex`、`.lst`、`.map`、`.dep`、`.lnp`、`.sct`、`.uvoptx`、`.uvguix.*` 等；
- 重复的 `程序源码/STM32Project-无注释版`（与 `JiangKe_Examples` 内容重复，仅注释不同）；
- `Keil5 MDK` 安装包/支持包（含超过 200 MB 的安装程序）；
- `模块资料` 厂商模块资料包（体积大，多数是厂商示例/图片）；
- `工具软件/STLINK Utility` 安装程序；
- 0 字节的库文件 `.lnk`（不是 Windows 快捷方式，但为避免误解已排除）；
- 压缩包和原始 `.zip` 库包。
- 当前仓库没有超过 200 MB 的文件；最大文件约 **18.7 MB**（标准库 CHM 帮助文件），因此不需要 Git LFS。

## 注意事项

- 源码编码不完全统一：部分江协/标准库文件是 GBK，部分个人代码是 UTF-8；中文注释乱码时请切换 GBK/GB18030 或 UTF-8。
- CMake 示例的 `.vscode` 配置是“能跑通的原作者环境”，不是通用配置；换电脑要改路径。
- `2.测频率` 的 PWM 输出在 PA0（TIM2_CH1），输入捕获在 PA6（TIM3_CH1），需要把 PA0 和 PA6 短接/回环才能测到频率。
- `CMake_Toolchain` 里的 `build/` 是生成目录，已排除；重新配置即可恢复。
- 工具软件中的 exe/dll 为第三方工具，Windows Defender 可能会提示；请从官方渠道确认后再运行。

## 致谢

- 江协科技（江科大）STM32 教程与例程：<https://jiangxiekeji.com>
- STMicroelectronics STM32F10x 标准外设库
- 其他模块资料与工具的原作者/厂商

---

## English Summary

This repository contains:

- `firmware/JiangKe_Examples`: 43 STM32F103 examples from JiangKe (江协科技), self-contained with their own `Library/Start/System` copies.
- `firmware/MDK_Tests`: personal Keil MDK tests, including a minimal GPIO project and a PWM + input-capture frequency measurement project.
- `firmware/CMake_Toolchain`: a CMake + `arm-none-eabi-gcc` + OpenOCD + VS Code setup with a USART1 text-protocol test (`@LED_ON`, `@LED_OFF`).
- `firmware/StdPeriph_Lib`: STM32F10x Standard Peripheral Library V3.5.0.
- `docs/reference`: reference manuals, Cortex-M3 guide, datasheets, pinout.
- `tools`: serial assistant, FlyMcu, ST-Link/CH340 drivers, UltraCodingSwitch, `keilkill.bat`.

Build with Keil MDK by opening any `.uvprojx`, or with CMake/Ninja using `arm-none-eabi-gcc`. The VS Code configs contain absolute paths from the original machine and must be updated.

Build outputs, duplicate unannotated sources, the Keil installer, vendor module packages, and archives were moved outside the repository to `D:\Dev\STM32开发_excluded`. No file exceeds 200 MB (largest is about 18.7 MB). Source encodings are mixed (GBK/UTF-8); switch encoding if Chinese comments are garbled.

