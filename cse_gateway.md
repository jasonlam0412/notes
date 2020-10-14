# Guide To Submission



Okay so the submission process took longer to figure out than it should so here is a guide for other people like me who haven't used their UNIX mail before.



\1. Follow the Assignment PDF to obtain a <username>.tar.gz file.

\2. move file to sparc1 server using:

```
scp <username>.tar.gz <username>@gw.cse.cuhk.edu.hk:~/
```

\3. Log into gateway by:

```
ssh <username>@gw.cse.cuhk.edu.hk
```

\4. Log into sparc1 from gateway:

```
ssh <username>@sparc1
```

\5. Sparc1 will prompt you for a Terminal type, enter:

```
linux
```

\6. Make sure your file is the home directory by typing

```
ls <username>.tar.gz
```

\7. Enter:

```
uuencode <username>.tar.gz <username>.tar.gz | mailx -s "HW1 <your-sid> <Your-name>" csci3180@cse.cuhk.edu.hk
```

\8. Check submission in submission list

Can a TA please check if these steps are correct. Thanks