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
<!-- # fill_env_list
    if env is NULL set env_var $(PATH) | $(PWD) | $(SHELL_LVL)
# exit status
    exit with the correct exit status;
    add env_var $($) and store in side it the exit status of each exit
# expand heredoc input
    if the input is a values get the value and replace it
# signals in heredoc
    exit the heredc without killig the process
use only a global veriable for signal (sg_int) && replace exits stats with a envirement variable "?" and make a function if not u already made to set a specific envirement in the linked list  -->

alel-you@e1r2p1:~/Desktop/minishell.tet$ cat << "$HOME"
> "$USER"
> $USER
> "$HOME"
> $HOME
"$USER"
$USER
"$HOME"
alel-you@e1r2p1:~/Desktop/minishell.tet$ 

=================================================================
==1959879==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000018 (pc 0x0000004da78c bp 0x7ffc38ae9e90 sp 0x7ffc38ae9df0 T0)


env var name --> [A-Z][a-z][0-9][_] => first character can't be a number

~/minishell$ ✗🤯✗ export x="a=b c"
~/minishell$ ✗🤯✗ export | tail -n2
declare -x x="a=b"
declare -x c

~/minishell$ ✗🤯✗ echo alshjasd > /dev/full 
alshjasd
sh-5.2$ echo alshjasd > /dev/full
sh: echo: write error: No space left on device
sh-5.2$ echo $?
1


➜  minishell git:(free) ✗ ./minishell
~/minishell$ ✗🤯✗ < ´ | cat
[1]    1970270 segmentation fault (core dumped)  ./minishell
➜  minishell git:(free) ✗ ./minishell
~/minishell$ ✗🤯✗ < - | cat
[1]    1970434 segmentation fault (core dumped)  ./minishell


~/minishell$ ✗🤯✗ < '' | >'' ls
free(): double free detected in tcache 2
[1]    1973935 IOT instruction (core dumped)  ./minishel

~/minishell$ ✗🤯✗ << l | ls
> l
[1]    1979094 segmentation fault (core dumped)  ./minishell