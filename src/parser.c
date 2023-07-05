/* 
    Display a promt while waiting for a new commmand.
    Have a working history.
    Find and launch executables (using the PATH variable or an absolute path).
    Handle ' (single) and " (double) quotes like in bash.
    Implement redirections such as:
        < redirect input.
        > redirect output.
        << heredoc (doesn't affect history).
        >> redirect output in append mode.
    Implement | (pipes).
    Handle environment variables.
    Handle $?.
    ctrl-C, ctrl-D, and ctrl-\ should behave like in bash.
    Recreate the following builtins:
        echo with option -n.
        cd with only a relative or absolute path.
        pwd (no flags).
        export (no flags).
        unset (no flags).
        env (no flags or arguments).
        exit (no flags).
 */