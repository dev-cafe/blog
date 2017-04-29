---
layout: post
title: Peer-reviewed installation pipelines
status: wip
author: Radovan Bast
summary: Reproducible and transparent installation workflow for computing centers
---

## Abstract

This post describes how software installations are typically carried out and
maintained on computing centers and suggests how software installation could be
managed instead and motivates why: We suggest to script installations, to
document these scripts in a Git repository, to use forks to contribute
installation recipes, to test and deploy installations via continuous
integration pipelines, to employ code review for quality assurance and
feedback, and finally to share everything transparently for the great good of
the community. It is possible that the approach described here is already in
operation somewhere - it is a relatively standard DevOps approach - in this
case please let us know and share your lessons learned!


## Typical software installation on a typical computing center

Academic computing clusters typically provide a Linux environment, as well as
installations of basic system software, compilers, libraries, tools, and
specialized research software which is used by students and researchers across
essentially all scientific disciplines.

These compilers, tools, and research codes are often installed "manually" and
here "manually" typically means executing `configure && make && make install`
steps or their equivalent in order to configure the build and subsequently
compile and install the binaries and/or libraries. Typically several versions
of a specific library or code are maintained and normally old versions are
never removed in order to not compromise reproducibility of scientific results.

Since computing clusters are highly customized and often non-uniform compared
to other sites, the configuration step typically requires customization to
obtain a correct and efficient installation. This means that installations on
clusters can be non-trivial and are often not a matter of minutes but the
process can take hours or even days and sometimes requires significant reverse
engineering efforts.

To avoid repeating this possibly labor-intensive experience when bumping
versions or reinstalling code after a new hardware procurement, the
installation and customization steps are typically documented in README files
or scripts of varying quality, reproducibility, and availability. As a curious
side-note, the README files and installation scripts are often not shared with
users - they are not actively hidden but also not actively shared either.

To remove the manual labor effort and to streamline and homogenize the setup in
particular for large teams, centers often develop home-cooked deployment
recipes, or in recent years move gradually to increasingly popular package
management systems such as [EasyBuild](https://easybuild.readthedocs.io) or
[Spack](https://computation.llnl.gov/projects/spack-hpc-package-manager). The
huge bonus of the latter two frameworks is the possibility to avoid reinventing
wheels and to leverage knowledge across different sites and stand of the
shoulders of others or to contribute to a community-driven installation
knowledge base and thus provide shoulders for our colleagues.


## Breakage and confusion despite best intentions

So things are becoming more and more automatized which gives the computing
center staff more time to do more interesting things. Still, problems remain:
Installations are still often carried out manually although they could be fully
scripted. Persons installing software still have to be careful to install
software in the right place, under the right user, with right permissions,
using the right naming, to document the installation in the right place
according to some agreed standards. In addition, not all software is currently
covered under [EasyBuild](https://easybuild.readthedocs.io) or
[Spack](https://computation.llnl.gov/projects/spack-hpc-package-manager) so
sometimes one needs to default to editing old-school configure scripts. It is
very difficult for novice staff and basically impossible for external staff or
site users to contribute installations without considerable effort for the
staff. And whether old-school or [EasyBuild](https://easybuild.readthedocs.io)
or [Spack](https://computation.llnl.gov/projects/spack-hpc-package-manager),
installations still can fail which means they need to be first carried out in a
safe place which increases complexity. If the test installation breaks or is
aborted, it may be hard to trace for other people. If it is successful, it
still needs to be repeated in the production environment. Sometimes the test
was successful but happened before the weekend or before the vacation and then
it is easy to forget a step and break production.

And although we have scripts and systems of varying sophistication it is both
embarrassing and frustrating to admit that we are often still not completely
sure *who* installed a particular software *when* and *how* precisely
(timestamps and file permissions are often not enough).

To avoid this, the entire team needs to agree on standards and these standards
need to be documented, communicated to all staff, read, understood, and
remembered. This requires discipline and discipline is hard to keep up on a
very complex environment when constantly context switching between tasks and
projects. In short, it is not too difficult to break things with best
intentions and so things do break.


## Delegate work to machines

So we want to try a better way. What exactly do we wish to achieve?

- Avoid boring work and routine steps.
- Fully reproducible installations.
- Traceable installations (no more confusion about who, what, when, and how).
- Do not break production: Isolation between testing and production
  environment.
- Deploying to the production environment has to be simple: No double work when
  going from testing to production.
- Openness and transparency so that anybody can reuse installation
  instructions.
- Possibility to contribute installations for non-staff.
- Possibility to review installations according to site standards.

Let us use existing technology to solve this!

First of all, **installations have to be scripted**. If they are not scripted,
they are not easily reproducible.  If they are scripted, they are automatically
documented. To this you may now be tempted to point out: "But often I first
need to experiment and tweak until I can fully script things." - The answer to
this is to experiment and tweak *with scripts*. Interactive sessions are not
easily reproducible for you or others.

We wish to know who exactly installed what exactly how exactly. This is
achieved by tracking the installation scripts in a **Git repository**.
Sometimes you notice that something broke on a particular day. Would be nice to
go back to that day to figure out what we installed that day and see whether
there is any correlation or effect at distance.  Good news is that with a Git
repository that is simple to find out.

**Nobody pushes to this repository directly**, not even the maintainers. All
contributions to this Git repository are submitted via fork/ pull-request
mechanism. This allows for equal access and equal rights for everybody. It also
allows to implement code review and automatize sanity checks.

Installations can be carried out in your home directory as a normal user
without any special permissions. Once you have calibrated the installation
script and you are ready to contribute the new script via fork/ pull-request
towards the upstream repository. **A pull request triggers a continuous
integration (CI) runner which carries out the installation in a well defined
and isolated environment and reports the result to the code review**.  The
pipeline can for instance trigger installation scripts in paths which have
changed since the last deployment. If the CI pipeline reports success, the
commit can be accepted to the upstream branch which triggers deploying the
installation on the production system, update of the documentation, and refreshing the module
tree. All this does not need to be done manually.
It is then also possible to
automatically post a tweet informing about the newly installed version or
update the message of the day, etc. Sometimes the entire system needs to be
reinstalled.  Fortunatelly, in this scheme this is an automatic process which
can run over the weekend.

Since no installation is done directly, there is no room for errors in the
choice of path, naming, or file permissions. All this can be encoded into the
CI pipeline and thus the **CI pipeline can be set up to guarantee well defined
paths and permissions**.

Accepting a pull-request means deploying and publishing an installation.
**Deploying an installation reduces to accepting a pull request**. As a
maintainer all you need to do is to define rules and to visually inspect
whether the build and possibly tests passed and the maintenance reduces to a
mouse click. Of course if the CI pipeline fails, the pull request is rejected
and the contributor needs to go back to the drawing board.


## Go public and decentralize

The repository should be public and placed in a prominent public place such as
[GitHub](http://github.com) or [GitLab](http://gitlab.com). All installation
decisions are transparent. This is important for reproducibility.  There is
nothing to hide. For proprietary software we are not allowed to publish the
code but nothing speaks against publishing the precise steps we have taken to
install it.

This transparency makes it easy for users to install their own versions and
experiment with further customization.

Since the repository is public, anybody can contribute fixes and installation
recipes. The center can now involve external experts, vendors, experienced
users, application experts abroad, etc.


## Caveat

Do not install a Trojan horse: verify scripts from untrusted sources and use
checksums.


## Conclusions

We care about reproducibility and thus believe it is important to script all
installation steps. We believe it is a win-win situation to make the
installation steps public, accessible, and reproducible.  We recommend to track
installations in a Git repository to track the timeline, authors, and
decisions.  All installation steps are contributed via fork/ pull-request,
automatically tested with a configurable CI pipeline and reviewed before they
are deployed to the production environment.  Since the repository is public,
the fork/ pull-request workflow allows to fork, share, adapt, and contribute
installations for everybody.
