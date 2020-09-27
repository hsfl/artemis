---
title: COSMOS Tutorial Part 1 - COSMOS and QtCreator
permalink: /pages/tutorials/cosmos/cosmos1.html
layout: series

tags: [software]
keywords: software
toc: false

series:
    language: "C++"
    next: /pages/tutorials/cosmos/cosmos2.html
---


> **_Note:_** Not using the Artemis Development Environment? Then you should first follow the instructions for
> [installing COSMOS from scratch]({{site.folder_tutorials_from_scratch}}/cosmos-from-scratch.html).


## Introduction
QtCreator is an IDE (integrated development environment) targeted at C/C++ developers, and is included in the [Artemis Development Environment]({{site.folder_docs_other}}/development-environment.html) by default.


## Clone the SimpleAgent Template Project



Open up a new terminal (<kbd>Control</kbd> + <kbd>Alt</kbd> + <kbd>T</kbd>) and change directory to any folder you
wish to place the SimpleAgent template project. For this tutorial we'll be using the home directory.

In the terminal, run the following command to clone the SimpleAgent template project:

```bash
git clone https://github.com/mtmk-ee/simpleagent_template
```

This will download the template to a directory called `simpleagent_template`.

Once it's finished downloading, open up QtCreator and go to _File_ -> _Open File or Project..._, and open the file `simpleagent_template/CMakeLists.txt`. This file contains the project configuration, and lets Qt Creator know how
the project is structured.

{% include image.html file="/resources/tutorials/cosmos/part1/open_project_window.png" %}


{% include important.html content="If this is your first time working with the project or you have
recently updated your software, you may be met with a `Configure Project` page.
Select both the `ARM32` kit and the `Desktop` kit, then click the `Configure Project` button." %}

The project `simpleagent_template` will appear in the navigation pane on the left side of the window (you can always rename the project by editing the `CMakeLists.txt` file). Expand the project (double click), as well as the `source` folder, then expand the target `my_agent` and open the source file `my_agent.cpp`.

You should now see the `my_agent.cpp` source code in the editor.



{% include image.html file="/resources/tutorials/cosmos/part1/open_file.png" width="100%" %}
