---
layout: post
title: Branching Models
author: Roberto Di Remigio
summary: Debugging the branching model
---

## Attendees

Radovan Bast, Roberto Di Remigio and Giacomo Tartari

## Agenda

### Branching Models

* Continue the discussion on branching models for collaborative development using Git.

## Notes

### Branching Models

* Based on ![the new picture](https://cdn.rawgit.com/robertodr/branching-model-discussion/0bb91fa7/images/branching_model-v2.png)
  we discussed some more the role of the various branches with valuable input
  from Giacomo.
  Radovan rewrote the text in the
  [README.md](https://github.com/robertodr/branching-model-discussion/blob/master/README.md)
* We found that defining the role `cherry-pick` and `merge` actions is either
  too complicated or too ambiguous without a working example of the branching
  model. We decided to test run the model and then come back to these details.

## Action Items

### Branching Models

* Roberto will adopt the branching model in [PCMSolver](https://github.com/PCMSolver/pcmsolver)
* We still need to draft a `CONTRIBUTING.md` based on the description of the branching model.
  This is postponed until after the test run for the branching model.
