---
layout: post
title: Show code changes when you edit the Git commit message
author: Radovan Bast
---

Try this next time you want to commit a change:

```shell
$ git commit -v
```

It shows you the diff while you edit the commit message. No more quitting the
editor just because you do not remember the name of a variable.
