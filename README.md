# JLU大一课设学生成绩管理系统
主要功能概述
1.登录模块：
  1）选择登录身份：
       可选择以教师身份登录教师端或以学生身份登录学生端
2）教师登录：
     选择教师身份后，输入教师的账号和密码进行登录，若账号与密码均正确则跳转教师端
     否则提示登录失败，用户重新输入。
3）学生登录：
选择学生身份后，输入学生的账号和密码进行登录，若账号与密码均正确则跳转教师端
      否则提示登录失败，用户重新输入。

2.教师端模块：
1）录入：
能够录入学生信息，包括学生姓名，学号，对应课程成绩以及素质类加分，同时为学生生成可登入学生系统的学生账号。新录入学生学号不可与已有学生学号相同，若出现相同，系统会提示错误。
能进行课程的录入，录入其名称、编号、对应学分。新录入课程编号不可与已有课程编号相同，若出现相同，系统会提示错误。
2）浏览：
能够遍历打印所有已经录入学生的所有信息。若还未录入学生信息，系统会提示错误。（此错误提示适用于以下可能出现此错误的所有功能）
3）排序：
能够按照学生学号或GPA成绩顺序打印所有学生信息，并将排序保存至文件。
4）查找：
能够按照学生学号，姓名打印某位特定学生的信息。若未找到对应学号的学生系统会提示错误（此错误提示适用于以下可能出现此错误的所有功能）
5）修改：
能够按照学生学号对某位特定学生的信息进行修改。
6）删除：
能够按照学生学号对某位特定学生的全部信息进行删除。
能够按照学生学号对某位特定学生的指定课程成绩进行删除/
7）教师注册：
能够通过教师工号进行另一个教师工号的注册，新录入教师账号不可与已有教师账号相同，同时包含对教师身份的检验功能（输入检验码）。
8）课程管理：
能够增加或删除学生的应休课程，同时录入课程应包含的信息。
9）素质加分管理：
 能够增加或删除学生可获得的素质类加分项目，同时录入素质加分项应包含的信息。
3.学生端功能:
         1） 查询：能够按照学生登录的账号打印账号下对应的学生信息。
         2）密码修改：能够按照学生学号修改对应账户下的学生账号密码，过程包括旧密码的检验与新密码的输入。
