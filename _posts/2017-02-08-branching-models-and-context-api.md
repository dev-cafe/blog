---
layout: post
title: Branching Models and Context API
author: Roberto Di Remigio
summary: Software development discussion cafè kick-off!
---

## Attendees

Radovan Bast and Roberto Di Remigio

## Agenda

### Branching Models

* Discussion on branching models for collaborative development using Git. Based
  on [this draft document on
  GitHub](https://github.com/robertodr/branching-model-discussion)

### Context API

* Discussion on the bug reported on [GitHub](https://github.com/bast/context-api-example/issues/1)

## Notes

### Branching Models

* Radovan’s model doesn’t have enough semantic flexibility to make clear where
  bugfixes should go and where functionality improvements should go. It is,
  however, very clear when API breaking changes happen and where these should
  go, relative to upstream repo and branches.
* Roberto’s model has ambiguities regarding API breaking changes.
* A finer grained model, synthesis of the two, has the desired semantics. ![See
  photo](../images/posts/2017-02-08_branching-model.jpg "Branching model")

### Context API Bug

* The problem comes about because the context object is just an opaque handle
  to a C++ object that can be vastly more complicated.
* We explored the problem using valgrind and the GCC undefined behavior and
  address sanitizers.
* Conclusion: track the initialization status of the C++ object, insert checks
  where appropriate and throw/abort when client tries to access the API before
  initialization/after finalization. This avoids having to invalidate the
  pointer host-side after a call to the api_delete API function.

## Action Items

### Branching Models

* Roberto will update the branching model document.
    - Draw SVG picture corresponding to the one drawn on the board [see
      photo](https://github.com/robertodr/branching-model-discussion/issues/1)
    - Write down some words
    - Possibly address [this issue](https://github.com/robertodr/branching-model-discussion/issues/2)

## Next Meeting Agenda

**Next meeting will take place March, 1st at 11:00 AM in Radovan’s office**

* **CI service** Draft requirements on the CI server capabilities. Radovan
  might have some news on a guinea pig machine.
* **Branching models** Finalize discussion, possibly write a blog post.
* **Library design** Radovan prepared a
  [repository](https://github.com/bast/library-design) and Roberto uploaded the
  brainstorming document. We should move forward with this project.
