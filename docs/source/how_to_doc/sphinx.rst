Sphinx
======

Sphinx is a powerful tool for creating documentation,
and RST (reStructuredText) is the markup language commonly used with Sphinx.
When combined with the sphinx_design extension, it becomes even more versatile,
allowing you to create visually appealing and well-organized documentation.

Basic Structure
---------------
Each RST file begins with a title and underline it with dashes (``=``).
For example:

.. code-block:: rst

    My Awesome Project
    ==================

More content goes below the title

Headings
--------

Use different levels of headings to structure your content.
(Use ``=`` for top-level headings, ``-`` for second-level headings)
Please always use as many dashes as characters in the heading:

.. code-block:: rst

    Installation
    ------------

others are: ``.``, ``#``, ``~``, ``^``, `````, ``+`` (and more...)

Text Formatting
---------------
Test can be written normally below headings.

.. code-block:: rst

    Installation
    ------------

    My informative text

Lists
-----
Use asterisks * for bullet lists:

.. tab-set::

    .. tab-item:: Result

        * Get up George, you’re embarrassing me.
        * Chatfield, there seems to be something wrong with our bloody ships today.
        * I can’t wear beige because nobody would know who I am.
        * We had a very serious evening you know.

    .. tab-item:: Code

        .. code-block:: rst

            * Get up George, you’re embarrassing me.
            * Chatfield, there seems to be something wrong with our bloody ships today.
            * I can’t wear beige because nobody would know who I am.
            * We had a very serious evening you know.


And numbers for numbered lists:

.. tab-set::

    .. tab-item:: Result

        1. By God, sir, I’ve lost my leg!
        2. By God, sir, so you have!
        3. We are still open – more open than usual
        4. I told you I was ill.

    .. tab-item:: Code

        .. code-block:: rst

            1. By God, sir, I’ve lost my leg!
            2. By God, sir, so you have!
            3. We are still open – more open than usual
            4. I told you I was ill.

Links
-----
Create links using the link text <URL> syntax:

.. tab-set::

    .. tab-item:: Result

        For more information, visit the `official website <https://example.com>`_.

    .. tab-item:: Code

        .. code-block:: rst

            For more information, visit the `official website <https://example.com>`_.

Images
------
Images can be added easily. But using urls for images is recommended.

.. tab-set::

    .. tab-item:: Result

        .. image:: https://github.com/FrederoxDev/Amethyst/assets/69014593/08e43b26-05e2-4646-968b-0d3ab6699d78
            :alt: Amethyst logo
            :width: 100
            :height: 100

    .. tab-item:: Code

        .. code-block:: rst

            .. image:: https://github.com/FrederoxDev/Amethyst/assets/69014593/08e43b26-05e2-4646-968b-0d3ab6699d78
                :alt: Amethyst logo
                :width: 100
                :height: 100

Code Blocks
-----------
Code blocks are great for showing off amazing code.

.. tab-set::

    .. tab-item:: Result

        .. code-block:: python

            print("Hello, World!")

    .. tab-item:: Code

        .. code-block:: rst

            .. code-block:: python

                print("Hello, World!")

Languages like C/C++, Java, Js, Rust and others are also supported, for a list of supported languages visit the `pygments website <https://pygments.org/languages/>`_

Tables
------
There are many ways of creating a table, but we recommend using the following syntax:

.. tab-set::

    .. tab-item:: Result

        +--------------+--------------+
        | Header 1     | Header 2     |
        +==============+==============+
        | Row 1, Col 1 | Row 1, Col 2 |
        +--------------+--------------+
        | Row 2, Col 1 | Row 2, Col 2 |
        +--------------+--------------+

    .. tab-item:: Code

        .. code-block::

            +--------------+--------------+
            | Header 1     | Header 2     |
            +==============+==============+
            | Row 1, Col 1 | Row 1, Col 2 |
            +--------------+--------------+
            | Row 2, Col 1 | Row 2, Col 2 |
            +--------------+--------------+


Toc Trees
---------
TOC (Table Of Contents) trees provide users with a hierarchical overview of documentation.
These TOC trees can be automatically generated using the toctree directive.
For example:

.. code-block:: rst

    .. toctree::
        :maxdepth: 2
        :caption: Contents:

        introduction
        installation
        usage
        configuration
        api-reference
        examples
        contributing-guidelines
        license

Entries like ``introduction``, ``installation`` or ``usage`` are other files who's content is loaded and shown
the depth of this is dictated by ``:maxdepth:`` and the title by ``:caption:``.
More options are ``:hidden:`` to, who guessed it, hide the toc (it will still be used for the sidebar)
or ``:titlesonly:`` which allows to just show the titles of pages.

To learn more about toc (-trees) visit the official `Sphinx Documentation <https://sphinx-doc-zh.readthedocs.io/en/latest/markup/toctree.html>`_

Sphinx
------
You can read more about sphinx's rst styling on the `Sphinx Website <https://www.sphinx-doc.org/en/master/usage/restructuredtext/index.html>`_

Sphinx Design
-------------
Vanilla rst & sphinx have a lot of options, but still certain things are missing.
This is where ``sphinx_design`` is useful.
It opens the possibility for adding more useful design elements, like:
Grids, Cards, Dropdowns, Tabs, Badges, Buttons & Icons...

The entire documentation for ``sphinx_design`` can be found on the `sphinx design website <https://sphinx-design.readthedocs.io/en/latest/index.html>`_.

Awesome Sphinx Theme
--------------------
We use the `Awesome Sphinx Theme <https://sphinxawesome.xyz>`_ in our documentation.
It is the most beautiful theme for sphinx that we could find.
We actively try to communicate with the authors to improve this theme in the future.
