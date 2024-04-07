# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = build

BREATHE_DEFAULT_PROJECT = AmethystApi
BREATHE_OUTPUT = source/breathe
# possible are list of: class, interface, struct, union, file, namespace, group
BREATHE_GENERATION_OPTIONS = file
DOXYGEN_OUTPUT = source/doxygen

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Generate all doxyfiles
doxygen:
	doxygen ../AmethystAPI/.doxyfile

.PHONY: doxygen Makefile

# Generate all rst files from the doxyfiles
breathe_apidoc:
	breathe-apidoc -o $(BREATHE_OUTPUT) -p $(BREATHE_DEFAULT_PROJECT) -g $(BREATHE_GENERATION_OPTIONS) $(DOXYGEN_OUTPUT)

.PHONY: breathe_apidoc Makefile

# Build the sphinx html docs
sphinx_build:
	make html

.PHONY: build Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

