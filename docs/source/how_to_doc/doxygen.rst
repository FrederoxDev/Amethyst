Doxygen
=======

Doxygen is a powerful documentation system for C++, C, Java, Objective-C, Python, and other languages.
It generates documentation from annotated source code.
Here's a guide on how to document C++ code using Doxygen comments effectively for the Amethyst Codebase.

.. note::
    All comments for amethyst code should be done in the header files (``.hpp``)

Writing Doxygen Comments
------------------------
Doxygen supports various styles for documenting code,
but the most common one is the Javadoc-style comments. These comments start with ``/**`` and end with ``*/``.

Here is a simple example:

.. code-block:: cpp

    /**
     * @brief Brief description of the function or class.
     *
     * @param parameter_name Description of parameter.
     * @return Description of return value.
     * @throws ExceptionName Description of exception (if any).
     */

There are also many different Annotation types, the most useful are listed here:

+-----------------+---------------------------------------------+---------------------------------------------+
| Annotation      | Description                                 | Example                                     |
+=================+=============================================+=============================================+
| ``@brief``      | Provides a brief description of the item.   | ``@brief`` This function calculates the sum |
|                 |                                             | of two numbers.                             |
+-----------------+---------------------------------------------+---------------------------------------------+
| ``@details``    | Provides detailed information about the     | ``@details`` This function uses a recursive |
|                 | item, typically expanding on the brief      | algorithm to calculate the sum.             |
|                 | description.                                |                                             |
+-----------------+---------------------------------------------+---------------------------------------------+
| ``@param``      | Describes a parameter of a function or      | ``@param`` x The first number to be added.  |
|                 | method.                                     |                                             |
+-----------------+---------------------------------------------+---------------------------------------------+
| ``@return``     | Describes the return value of a function    | ``@return`` The sum of the two numbers.     |
|                 | or method.                                  |                                             |
+-----------------+---------------------------------------------+---------------------------------------------+
| ``@note``       | Provides additional notes or information    | ``@note`` This function assumes that the    |
|                 | about the item.                             | numbers are integers.                       |
+-----------------+---------------------------------------------+---------------------------------------------+
| ``@warning``    | Indicates a warning related to the item.    | ``@warning`` This function may produce      |
|                 |                                             | unexpected results for negative             |
|                 |                                             | numbers.                                    |
+-----------------+---------------------------------------------+---------------------------------------------+
| ``@todo``       | Marks a todo item or a task that needs to   | ``@todo`` Implement error handling for      |
|                 | be completed or addressed.                  | invalid inputs.                             |
+-----------------+---------------------------------------------+---------------------------------------------+
| ``@deprecated`` | Indicates that the item is deprecated and   | ``@deprecated`` Use the newSum() function   |
|                 | will be removed in future versions.         | instead.                                    |
+-----------------+---------------------------------------------+---------------------------------------------+

.. hint::
    Here is more information about the javadoc style used by doxygen on `Oracle's Website <https://www.oracle.com/technical-resources/articles/java/javadoc-tool.html>`_

Examples
--------

Documenting Functions:

.. code-block:: cpp

    /**
     * @brief Brief description of the function.
     *
     * @details Detailed description of what the function does.
     *
     * @param param1 Description of parameter 1.
     * @param param2 Description of parameter 2.
     * @return Description of return value.
     */
    int add(int param1, int param2) {
        return param1 + param2;
    }

Documenting Classes:

.. code-block:: cpp

    /**
     * @brief Brief description of the class.
     *
     * @details Detailed description of the purpose of the class.
     */
    class MyClass {
    public:
        /**
         * @brief Brief description of the constructor.
         *
         * @details Detailed description of what the constructor does.
         *
         * @param param Description of parameter.
         */
        MyClass(int param);

        /**
         * @brief Brief description of a member function.
         *
         * @details Detailed description of what the member function does.
         *
         * @param param Description of parameter.
         * @return Description of return value.
         */
        int memberFunction(int param);
    };

Additional Tips
---------------

- Keep comments concise but informative.
- Use proper formatting for better readability.
- Update comments when code changes to keep documentation accurate.
- Using ai to generate comments could be used, but the results should always be checked by a human.