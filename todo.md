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



~/minishell$ ✗🤯✗ l
l :command not found

=================================================================
==1749544==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 64 byte(s) in 2 object(s) allocated from:
    #0 0x49a25d in malloc (/home/alel-you/Desktop/minishell.tet/minishell+0x49a25d)
    #1 0x4ce6f8 in new_redir (/home/alel-you/Desktop/minishell.tet/minishell+0x4ce6f8)
    #2 0x4ce89d in build_redir (/home/alel-you/Desktop/minishell.tet/minishell+0x4ce89d)
    #3 0x4cebef in build_cmd_helper (/home/alel-you/Desktop/minishell.tet/minishell+0x4cebef)
    #4 0x4ce677 in build_cmd (/home/alel-you/Desktop/minishell.tet/minishell+0x4ce677)
    #5 0x4cbd27 in main (/home/alel-you/Desktop/minishell.tet/minishell+0x4cbd27)
    #6 0x7f1868d57d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

Direct leak of 17 byte(s) in 3 object(s) allocated from:
    #0 0x49a25d in malloc (/home/alel-you/Desktop/minishell.tet/minishell+0x49a25d)
    #1 0x4d096e in here_doc (/home/alel-you/Desktop/minishell.tet/minishell+0x4d096e)
    #2 0x4cbd1e in main (/home/alel-you/Desktop/minishell.tet/minishell+0x4cbd1e)
    #3 0x7f1868d57d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

Indirect leak of 4 byte(s) in 2 object(s) allocated from:
    #0 0x49a25d in malloc (/home/alel-you/Desktop/minishell.tet/minishell+0x49a25d)
    #1 0x4cc1ee in ft_strdup (/home/alel-you/Desktop/minishell.tet/minishell+0x4cc1ee)
    #2 0x4ce736 in new_redir (/home/alel-you/Desktop/minishell.tet/minishell+0x4ce736)
    #3 0x4ce89d in build_redir (/home/alel-you/Desktop/minishell.tet/minishell+0x4ce89d)
    #4 0x4cebef in build_cmd_helper (/home/alel-you/Desktop/minishell.tet/minishell+0x4cebef)
    #5 0x4ce677 in build_cmd (/home/alel-you/Desktop/minishell.tet/minishell+0x4ce677)
    #6 0x4cbd27 in main (/home/alel-you/Desktop/minishell.tet/minishell+0x4cbd27)
    #7 0x7f1868d57d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: 85 byte(s) leaked in 7 allocation(s).
~/minishell$ ✗🤯✗ l








---------------------------------- BENITO ------------------------------------
~/minishell$ ✗🤯✗ ls ""
execution  inc  Makefile  minishell  src  test.c  todo.md  trash.c
check bash ;
< " "| ls
execution  inc  Makefile  minishell  src  test.c  todo.md  trash.c
also check bash
~/minishell$ ✗🤯✗ < $a
                
~/minishell$ ✗🤯✗ ls | < $a 

~/minishell$ ✗🤯✗ echo $a
$a
~/minishell$ ✗🤯✗ echoooo
~/minishell$ ✗🤯✗ 
aaa~/minishell$ ✗🤯✗ echoooo -nnnnnnnn -nnn aaa
aaa~/minishell$ ✗ echoooo -nnnnnnnn -nnn aaa
aaa~/minishell$ ✗🤯✗ cddddddd
~/minishell$ ✗🤯✗ pwd

=>>>
~/minishell$ ✗🤯✗ export AAA="''''''''''''''''"
~/minishell$ ✗🤯✗ export | grep AAA
declare -x AAA="''''''''''''''''"
~/minishell$ ✗🤯✗ export AAA=$AAA
~/minishell$ ✗🤯✗ export | grep AAA
declare -x AAA=""

~/minishell$ ✗🤯✗ export AAA="''''''''''''''''''"
~/minishell$ ✗🤯✗ $AAA
 :command not found

 ~/minishell$ ✗🤯✗ <la < ls

  echo $AAA"'$USER''$USER'" $AAA = "''"
'$USER''$USER'



void print_list(t_list *tokens)
{
	t_tokens *tmp;

	tmp = tokens->head;
	while (tmp != tokens->tail)
	{
		printf("---------------content------------- :%s\n", tmp->content);
		printf("---------------type------------- :%d\n", tmp->type);
		tmp = tmp->next;
	}
	printf("-------------content------------ :%s\n", tmp->content);
	printf("---------------type------------- :%d\n", tmp->type);
}

void print_cmd_list(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd)
			printf("cmd: %s\n", tmp->cmd);
		else if (tmp->redir->type == HRDOC)
			printf("%s\n", tmp->redir->file);
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->redir)
			printf("1111111111111111111111111111\n");
		if (tmp->cmd)
			printf("=====%s\n", tmp->cmd);
		else
		{
			t_redir	*redir = tmp->redir;
			while (redir)
			{
				printf("type=====%d\n", redir->type);
				printf("file=====%s\n", redir->file);
				redir = redir->next;
			} 
		}
		tmp = tmp->next;
	}
}

======
bash-3.2$ cd ..
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
bash-3.2$ pwd
/mnt/homes/yael-maa/minishell/1/2/..
bash-3.2$ cd .
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
bash-3.2$ pwd
/mnt/homes/yael-maa/minishell/1/2/../.
bash-3.2$ cd .
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
bash-3.2$ pwd
/mnt/homes/yael-maa/minishell/1/2/.././.
bash-3.2$ cd .
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
bash-3.2$ pwd
/mnt/homes/yael-maa/minishell/1/2/../././.
bash-3.2$ 
===mini===
~/minishell$ ✗🤯✗ mkdir -p 1/2
~/minishell$ ✗🤯✗ cd 1/2
~/minishell$ ✗🤯✗ pwd
/mnt/homes/yael-maa/minishell/1/2
~/minishell$ ✗🤯✗ rm -rf ../../1
~/minishell$ ✗🤯✗ pwd
pwd: No such file or directory
~/minishell$ ✗🤯✗ cd ..
~/minishell$ ✗🤯✗ pwd
pwd: No such file or directory
~/minishell$ ✗🤯✗ cd .
~/minishell$ ✗🤯✗ pwd
pwd: No such file or directory
======