# Multithreaded Journal

C++ Test Assignment: Multithreaded Log Writing Implementation 

(C/C++ Developer)

## Features

* Dynamic journal library.
* Thread-safe message passing through `ThreadSafeQueue`.
* Handling of input and writing errors.

## Running
input format: 

```text 
"path/to/file" -(l/m/h)
-l — LOW
-m — MEDIUM
-h — HIGH
```

The path can be either absolute or relative to the current working directory. 
The file name can be omitted. In this case, the journal is created in the current 
directory using the default name format:

```text
journal_%Y-%m-%d_%H:%M:%S.txt
```

The default severity level can also be omitted. In this case, `LOW` is used.

## Input Format

```text
"message" -(l/m/h)

```
The message level can be omitted. In this case, `LOW` is used.


To change default journal severity level, enter only -l/-m/-h:
```text
-m
```

The default message level cannot be changed - it is always `LOW`
default
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

```text
make
make test
./build/bin/app
```

