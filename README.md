# mydu

This exercise deals with the implementation of the Unix application known as du. The command du displays the size of
subdirectories of the tree rooted at the directories/files specified on the command-line arguments. If called with no argument,
the du utility uses the current working directory.

#The solution will be invoked using the following command:\
mydu [-h]\
mydu [-a] [-B M | -b | -m] [-c] [-d N] [-H] [-L] [-s] <dir1> <dir2> ...\
-a Write count for all files, not just directories.\
-B M Scale sizes by M before printing; for example, -BM prints size in units of 1,048,576 bytes.\
-b Print size in bytes.\
-c Print a grand total.\
-d N Print the total for a directory only if it is N or fewer levels below the command line argument.\
-h Print a help message or usage, and exit\
-H Human readable; print size in human readable format, for example, 1K, 234M, 2G.\
-L Dereference all symbolic links. By default, you will not dereference symbolic links.\
-m Same as -B 1048576.\
-s Display only a total for each argument.

Known issues:\
none

Git log:```bash
commit a9d24e0e869e85b2aeb7e785cf4cda6c77601939
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 20 15:01:12 2020 -0500

    added makefile

commit 00b450e4a34f420e8e0048fd25e139d1ecfd081d
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 20 14:48:56 2020 -0500

    added finishing touches and comments

commit e85ed7754c656d9e2ccd043ba7ed134603727f9e
Merge: da9225f 45ce39b
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 20 14:35:00 2020 -0500

    Merge branch 'master' of github.com:pango3001/mydu

commit da9225f5c0e438285f05b9d03d8ff444a0da3686
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 20 14:34:45 2020 -0500

    implemented l option

commit 45ce39b71cfbaccb8928ba691aadd9057ca2948c
Author: pango3001 <pango3001@gmail.com>
Date:   Sun Sep 20 14:08:26 2020 -0500

    Update README.md

commit 67db625dde4d96f108926e6e64a1b5556e5e97d1
Author: pango3001 <pango3001@gmail.com>
Date:   Sun Sep 20 14:07:35 2020 -0500

    Update README.md

commit 4aac43f3366000475862ab785d5804c78907e254
Author: pango3001 <pango3001@gmail.com>
Date:   Sun Sep 20 14:06:00 2020 -0500

    Update README.md

commit 7828d1daf002e88b06e391b13d609fd343e1ae8e
Author: pango3001 <pango3001@gmail.com>
Date:   Sun Sep 20 14:05:08 2020 -0500

    Update README.md

commit 38559d47164438617c2473692940681e21f54704
Merge: ba5f555 1a9a086
Author: pango3001 <pango3001@gmail.com>
Date:   Sun Sep 20 14:03:17 2020 -0500

    Merge branch 'master' of https://github.com/pango3001/mydu

commit ba5f5553a8db294112a2d118733a005dddac5e00
Author: pango3001 <pango3001@gmail.com>
Date:   Sun Sep 20 14:03:07 2020 -0500

    Update README.md

commit 1a9a086389e8328a9b17dde0997341dd4c46cc2b
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 20 14:00:38 2020 -0500

    implemented s option

commit caa510578021297e734b4687dd5eeb3916539574
Merge: bb9a88a 186cb34
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 20 13:11:29 2020 -0500

    Merge branch 'master' of github.com:pango3001/mydu

commit bb9a88aa3f9d554fa650228bca744894cd663e29
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 20 13:10:19 2020 -0500

    fixed option for depth

commit 2e47dd7c30de0ae8eb21cb7f809e2c3e263b5f2e
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 20 13:01:34 2020 -0500

    implemented option for depth

commit 186cb34bf3cd06a197bf83b44f60184469d19dd5
Author: pango3001 <pango3001@gmail.com>
Date:   Sun Sep 20 12:11:56 2020 -0500

    Update README.md
    
    added to readme

commit d20dabb8f64a77e79ecbf9f8b97ae0a28ee1f1b1
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 20 12:01:56 2020 -0500

    added comments

commit 404c36cedca9fc619fe4bfd49f328a739cf29a69
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Fri Sep 18 22:52:36 2020 -0500

    done for the night

commit 2ed42df622a92b98960825692be496dd9e085abc
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Fri Sep 18 21:30:36 2020 -0500

    added -H command

commit 71a3bafc0fb9d3fd2df425c80b1814c4cd59055f
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Fri Sep 18 20:35:42 2020 -0500

    added c option

commit da0d222f329e679ecb86824aba1f8ba7fe113ecf
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Tue Sep 15 22:25:00 2020 -0500

    stopping for the night

commit 840dca17a4a4df2d54f31f94904156e6666d5f7d
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Tue Sep 15 22:12:11 2020 -0500

    fixed the sum issue for option a

commit 08f5a0247e243644867d632c5b5c27dba86459f4
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Tue Sep 15 21:55:35 2020 -0500

    added -a option

commit dbc790bbe84920ab90a41b336b98ef9a86ec4242
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Tue Sep 15 21:29:25 2020 -0500

    counts files

commit 80882168ce9f2eecb6e5a97086fc330bce31689f
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Tue Sep 15 17:35:39 2020 -0500

    Removed testing code

commit 7fb5555cf1b388d369e252d1e21afb3707d31a0b
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Tue Sep 15 17:03:01 2020 -0500

    Finally have depthfirst function working and sizepathfun

commit 4c083925b19185c4c49489240a3d8b2f105688e3
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 13 21:39:28 2020 -0500

    working on recursion through directories

commit 136cac9a9dd92bbb95aaa4307a343c476516bfee
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Sun Sep 13 20:27:57 2020 -0500

    started over

commit 1c8bb245e7d967bf53c1faebf38bd06bbc7481fa
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Thu Sep 10 14:26:33 2020 -0500

    worked on depthfirst

commit a974d71adba6c6893bf7776b4ad5efc9852b969a
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Thu Sep 10 12:19:54 2020 -0500

    updates to get_dir function

commit 1d7939eb7b4528a745eaa4df7a03f19a4d263a00
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Thu Sep 10 11:26:27 2020 -0500

    added function to get current directory

commit 25376568465f5f5493822e16157f2db423000cf9
Author: Jesse McCarville <pango3001@gmail.com>
Date:   Wed Sep 9 20:05:39 2020 -0500

    first working with -h option

commit 21427e2b3618a1ca48c66e25aea7cda7d6fc541c
Author: pango3001 <pango3001@gmail.com>
Date:   Wed Sep 9 10:44:11 2020 -0500

    Add files via upload

commit 29462aab1f9e311849bb38b54ba1a86d8d94c24e
Author: pango3001 <pango3001@gmail.com>
Date:   Wed Sep 9 10:43:47 2020 -0500

    Initial commit

```

