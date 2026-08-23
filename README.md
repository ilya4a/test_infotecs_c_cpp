# Multithreaded Journal

Тестовое задание C++ -- многопоточная реализация
записи сообщений в журнал

## Features

* Dynamic journal library.
* Thread-safe message passing through `ThreadSafeQueue`.
* Handling of input and file-writing errors.

## Running

On startup, the application asks for:

1. The path to the journal file.
2. The default journal severity level.

```text 
"path/to/file" -(l/m/h)
-l — LOW
-m — MEDIUM
-h — HIGH
```

The path can be either absolute or relative to the current working directory. 
The file name can be omitted. In this case, the journal is created in the current directory using the following name format:

```text
journal_%Y-%m-%d_%H:%M:%S.txt
```

The default severity level can also be omitted. In this case, `LOW` is used.

## Input Format

A message can be entered as:

```text
"message" -(l/m/h)

```

The message level can be omitted. In this case, `LOW` is used.

To change the minimum journal severity level during runtime:

```text
-l
-m
-h
```

For example:

```text
"message" -m
-m
```

In the first case, a `MEDIUM`-level message is written to the journal. In the second case, the minimum journal severity level is changed to `MEDIUM`.
The default message level cannot be changed - it is always `LOW`

To exit the application:

```text
-q
```

To display the help message:

```text
--help
```

## Log Format

Each logged line contains the message timestamp, severity level, and message text:

```text
2026-08-23_04:04:03 low message 1
2026-08-23_04:04:19 medium message 2 
2026-08-23_04:04:39 high message 3
```

Changes to the journal level are also recorded as service messages:

```text
2026-08-23_04:04:43 journal level changed: medium
```

## Error Handling

Non-critical user input errors are handled without terminating the application:

```text
Error: missing closing quote
Error: invalid args...
Error: message is empty
Error: unknown log level
```

Critical errors related to the journal or file operations result in a controlled application shutdown with an appropriate error message.


## Examples 
```text
Enter filename and default log level (press Enter to use default):
Usage: --help

Journal created

Enter message: "text 1" 
Message sent

Enter message: "text 2" -h 
Error: unknown log level

Enter message: -m
Level changed
```

## Building


