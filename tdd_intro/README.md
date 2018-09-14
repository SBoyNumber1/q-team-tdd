## Abstract

This repository is a part of Eliademy course https://eliademy.com/app/a/courses/12ce8fba4c. See course overview for more details.

## Working on your own

To start working with this repo in your local environment you should download and install Qt Creator IDE and configure it.
Clone or fork this repo with git
```
$ git clone https://github.com/.../tdd-intro-practice.git
```

Create local branch with unique name (e.g. your name and surname or nickname)
```
$ git checkout -b BRANCH_NAME
```

Start doing things :)

## Layout

Note that there are three subroots in this project:

- [workshops](https://github.com/.../master/tdd_intro/workshops) - this is a root for all practice tasks, to be processed in group or demo mode
- [homework](https://github.com/.../master/tdd_intro/homework) - this is a root for all excercises proposed by course for your own practice at home
- [clean room](https://github.com/.../master/tdd_intro/cleanroom) - this is a root for the biggest conclusive part of course - complex task to implement
- 3rd_party - this is a place where all dependencies are stored. Each dependency has it's *.pri file under rootfolder (e.g. gtest.pri)

## Remarks

Note that gtest is compiled into static library with gtest_main implemented. It means that you do not have to implement _main_ function in your test projects.

## Links

For more of kata examples visit one of the following resources:

- http://exercism.io/
- https://www.codewars.com/
