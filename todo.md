// ali
<!-- command not found -->
<!-- 
# echo :
    echo -nnnnn -n fdfdf fe fef : -n fdfdf fe fef~/minishell$ -->

<!-- # cd :

    ~/minishell$ ✗ cd test/ minishell : bash: cd: too many arguments

    removed folder pwd : ~/minishell$ ✗ pwd
                        getcwd: No such file or directory
                        ➜  minishell.tet git:(copy) ✗  -->
<!-- cd without HOME (do not exit) :  tmptmptmp: Success --> -->
<!-- # pwd :
    getcwd: No such file or directory (do not exit) --> -->
# fill_env_list
    if env is NULL set env_var $(PATH) | $(PWD) | $(SHELL_LVL)
# exit status
    exit with the correct exit status;
    add env_var $($) and store in side it the exit status of each exit
# expand heredoc input
    if the input is a values get the value and replace it
# signals in heredoc
    exit the heredc without killig the process
use only a global veriable for signal (sg_int) && replace exits stats with a envirement variable "?" and make a function if not u already made to set a specific envirement in the linked list 
