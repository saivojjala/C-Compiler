# Lexical Analyser

## Phases of Lexical Analyser
* Scanning - Removing Comments, Removing Pre-Processor Directives, Removing Extra Whitespaces
* Lexical Analysis - Generating Tokens

## Implementation 
The program lexicalAnalyser.c reads a C program (sample.c) using fopen() function. This program first scans the given C code, checking and removing comments, whitespaces and pre-processor directives. After completion of scanning, it moves on to Lexical Analysis phase where it generates tokens of the form:
```
<lexeme name, row number, column number, lexeme type>
```

![Lexical Analyser](https://user-images.githubusercontent.com/75254081/195597379-9f3856bf-5587-4611-9ed4-aac9f463eb27.png)
