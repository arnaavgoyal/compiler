# compiler
My first ever attempt at making a compiler. Written in C, to compile C (or a vaguely C-style language).

## The Lexer
The lexer is declared in [tokenizer.h](../main/tokenizer.h) and defined in [tokenizer.c](../main/tokenizer.c).

It contains a set of functions to lex tokens with correct information on their type, as well as some functions the client code must use to manage token object allocation and deallocation.

The main lexing functionality is contained within `scan_next_token`.
It goes through each possibility of token one by one, until it finds the appropriate type.
  * Newline, EOF, and other whitespace are skipped.
  * Integer literals are detected by numeric characters, and are greedily lexed until the first non-numeric character.
  * Keywords and identifiers are detected by alphabetic characters, and are greedily lexed as well until the first non-alphabetic character.
  * Everything else is assumed to be an operator at first. Characters are greedily lexed until the first alphanumeric character. If the resulting token is not a valid token, characters are "un-lexed" until the longest valid operator is found.

Once a token has been lexed, it must be parsed.

## The Parser
The parser is declared in [parser.h](../main/parser.h) and defined in [parser.c](../main/parser.c)

Initially, the idea I had for the parser was for it to be contained within one giant function `parse`.
This function would call itself recursively in such a way that it could parse every possible language statement.
Of course, there are very good reasons as to why no compiler in existence does this, and I had to ditch that idea.

I then decided to attempt a recursive descent expression parser.
You can see the foundations of it in `unary_eval`, which parses unary operators as well as the base token that the operators are acting upon.
However, at this point, I had left this project to rot, so it is not functional :(

## Problems and Learnings
Every single design decision had sweeping repercussions that I didn't anticipate until it was too late.
Let's go over everything:

My language of choice was terrible. I love C, but it really does not work for a project like this.
  * The tokens that the lexer used had to be dynamically allocated and freed every single lex iteration. Manually.
  * Token lexing was exponentially harder because of C strings.
  * No classes made managing functionality encapsulation extremely infuriating.

My compiler state data design was bad.
  * The singular state object means that every single caller function of the lexer would have to cache the current line and column for every token in order to implement good location tracking for errors and refactoring.
  * The symbol table is two string arrays, which is simple, but horrible to actually use and query.

My lexer design was short-sighted - fast and simple, but with major pitfalls.
  * The lexer cannot distinguish between language keywords and identifiers. It lexes both as identifier tokens and leaves keyword identification to the caller.
  * The lexer has the list of operators hardcoded into it's source, so every operator addition required source code edits.

I then had to deal with these problems, compounded, in the parser.
  * Keyword detection when parsing is much harder than when lexing.
  * Lack of per-token state information made creating meaningful syntax errors impossible.
  * Lack of a proper token stream made it extremely difficult to do lookahead parsing, which is essentially a requirement for any compiler worth its salt.

# Conclusion
This project failed miserably as a functioning compiler, but it succeeded as a fun learning opportunity!
I learned a lot about program design, especially the importance of taking the time to make good design decisions.

This project is dead, but I used everything I learned to make a bigger and better compiler, [new-compiler](https://github.com/arnaavgoyal/new-compiler).
