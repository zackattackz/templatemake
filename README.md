# templatemake

This is a simple comand line program that utilizes [Inja](https://github.com/pantor/inja) to
fill out templates. `templatemake` takes in a template file and a data file as input and outputs
the filled out template to stdout. Optionally you can output the filled template to a file (or simply redirect stdout).
If you only have a template file and want to read data from stdin, or if you have a data file and want to read template from stdin
you can do that as well!

## Requirements

* [Inja](https://github.com/pantor/inja)
* [nlohmann's json](https://github.com/nlohmann/json)

## Installation

* `git clone` the source code.
* run `make` in the cloned repo
* `templatemake` should be generated, you can copy or move the executable to wherever you wish.

## Usage

`templatemake` will always require 5 arguements, so it will be run in this form...
`templatemake mode outfile_enabled templatefile datafile outfile

`mode` will be either: 
* `n` for normal (template file and data file are given)
* `d` for data (data file is given and template will be read from stdin)
* `t` for template (template file is given and data will be read from stdin)

if `outfile_enabled` is "y" then the filled template will be directed to the file path specified by `outfile`.
if it is anything other than "y" then output will go to stdout.

`templatefile`, `datafile`, and `outfile` are paths to the respective files.

For example if I have a file `template.txt` with the following:
`Hello {{ name }}!`
and a file `data.json` with the following:
`{"name","john"}`
then running `templatemake n no /path/to/template.txt /path/to/data.json -` will produce the output:
`Hello john!`

If I wanted to output that into a file `output.txt` I could run:
`templatemake n y /path/to/template.txt /path/to/data.json /path/to/output.txt`
