# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

According to Merriam-Webster's Medical Dictionary,
pneumonoultramicroscopicsilicovolcanoconiosis is a
pneumoconiosis caused by inhalation of very fine
silicate or quartz dust.

I'd also assume that it's the longest english word.

## According to its man page, what does `getrusage` do?

getrusage() returns resource usage measures for who, which can be one of the following.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

It appears that the rusage struct takes considerable chunk of memory so we better avoid making extraneous copies.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

It reads characters one-by-one into the word buffer until it reaches EOF. Words can only contain alphabetical
characters and apostrophes. Words that are longer than LENGTH and thus wouldn't fit into the buffer are dropped
entirely. Words which contain numbers are ignored completely as well. Whole words are then terminated
with a NUL character and checked against the dictionary of valid words.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Because %s would treat words containing numbers and other disallowed characters as valid which
based on our definition of the word is not.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

To declare that the data that the pointer points to must not be changed.
