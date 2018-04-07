#! /bin/bash

# 아주 비비로부터 데이터를 받아옵니다. 
################################################################################################

#바꿔주어야 하는 함수들 바꿔야하는함수.바꾸고자하는함수

CHSTR=("scanf_s" "scanf")
CHSTR_1=("system("pause")","system("read")")

USER_ID="northbrok04"
PASSWORD="비밀번호"

AJOUBB="https://eclass2.ajou.ac.kr" #아주비비
COURSE_ID="_33575_1" #프로그래밍 기초실습ID
COOKIES="cookies.txt" #쿠키 로그인정보 
ATTEMPT_ID=""
FILE_ID=""
FILE_NAME=""
LIST="$AJOUBB:8443/webapps/gradebook/do/instructor/viewNeedsGrading?sortCol=attemptDate&sortDir=ASCENDING&showAll=true&editPaging=false&course_id=$COURSE_ID&startIndex=0"
GREP_SEQ='<th  scope="row" class="" valign="top"><a aria-label=".[^ ][^ ][^ ]' 
ASSIGNMENT="/webapps/assignment/download?course_id="
PATH_TO_DOWNLOAD="PATH TO DOWNLOAD"
TOTAL=0
CNT_L=0
FAIL=0
STUDENT_NUM=0
CONT='n'
LOOPCNT=1
FILECNT=1
NAME="이상구"

# 과제 서버와 연결시도 인증

if ( $(wget -O Token "$AJOUBB" > /dev/null 2>&1) )
then
echo "[성공] 아주비비에 성공적으로 연결을 했습니다."

read -p "아이디 입력! : " USER_ID
read -p "비밀번호 입력! : " PASSWORD
clear
wget --post-data="userPw=$PASSWORD&userId=$USER_ID" "https://eclass2.ajou.ac.kr/webapps/bbgs-autosignon-BBLEARN/ajouLogin.jsp" -O Token >/dev/null 2>&1
wget --keep-session-cookies --save-cookies=./cookies.txt "https://eclass2.ajou.ac.kr$(cut -d^ -f3 < Token )" -O Token >/dev/null 2>&1

#쿠키확인
if [ -f "$COOKIES" ]
then

if( $(wget "$LIST"  -O $(date +'%Y%m%d').txt --load-cookies=$COOKIES >/dev/null 2>&1 )  )
then

grep "$GREP_SEQ" < $(date +'%Y%m%d').txt |grep -o '_[^ ][^ ][^ ][^ ][^ ][^ ]_[^ ]' >ID_LIST.txt
grep "$GREP_SEQ" < $(date +'%Y%m%d').txt |awk '{print substr($5,14,3)}' >name_list.txt

TOTAL=$(wc -l < name_list.txt)

echo "[성공] 총  $TOTAL 명의 과제 제출을 확인하였습니다 / 0명 이면 로그인 오류 "
echo "곧 과제함에서 제출자료를 받아옵니다!"
read -p "실행할까요? [ y / n ]" CONT

if [ "$CONT" = "y" ]; then

######출력폴더생성
if [ ! -d "download" ]; then
mkdir "download"
fi
#################


while [ $LOOPCNT -le $TOTAL   ]
do
##정보를 받아오면!
NAME="$(awk -v var=$LOOPCNT 'FNR==var {print $1 }' < name_list.txt)"
ATTEMPT_ID="$(awk -v var=$LOOPCNT 'FNR==var {print $1 }' < ID_LIST.txt)"
REDIRECTION="$AJOUBB/webapps/gradebook/do/instructor/performGrading?course_id=$COURSE_ID&source=cp_gradebook_needs_grading&cancelGradeUrl=%2Fwebapps%2Fgradebook%2Fdo%2Finstructor%2FviewNeedsGrading%3Fcourse_id%3D$COURSE_ID&mode=invokeFromNeedsGrading&viewInfo=%EC%B1%84%EC%A0%90+%ED%95%84%EC%9A%94&attemptId=$ATTEMPT_ID&groupAttemptId=;"
wget -O Token --load-cookies=./$COOKIES "$REDIRECTION" > Redirection 2>&1
TEMP="https:$(grep "https://eclass2.ajou.ac.kr/webapps/assignment" < Redirection |sed 's/^.*://' )"
wget -O LSG --load-cookies=./$COOKIES "$TEMP" >/dev/null 2>&1
grep '<a class="dwnldBtn" href="/webapps/assignment/download?' <LSG |awk '{print substr($3,92,9)}' > sub_file_id.txt
FILE_ID="$(awk -v var=$FILECNT 'FNR==var {print $1 }' < sub_file_id.txt)"
TOTAL_FILE=$(wc -l < sub_file_id.txt)
grep '<a class="dwnldBtn" href="/webapps/assignment/download?' <LSG |awk '{print substr($3,115,20000)}'> sub_file_name.txt
FILE_NAME="$(awk -v var=$FILECNT 'FNR==var {print $1 }' < sub_file_name.txt)"
FILE_NAME="${FILE_NAME%?}"
PATH_TO_DOWNLOAD="$AJOUBB$ASSIGNMENT$COURSE_ID&attempt_id=$ATTEMPT_ID&file_id=$FILE_ID&fileName=$FILE_NAME"


if [ ! -d "download/$NAME" ]; then
echo "$NAME 학생의 디렉토리를 생성중"
mkdir "download/$NAME"
fi

if( $(wget "$PATH_TO_DOWNLOAD" -O "download/$NAME/$NAME$FILECNT" --load-cookies=./$COOKIES > /dev/null 2>&1) )
then
echo "$NAME 학생의 자료 다운로드완료 [$LOOPCNT/$TOTAL]"
exten="$(echo "$FILE_NAME" |cut -d. -f2)"
mv download/$NAME/$NAME$FILECNT download/$NAME/$NAME$FILECNT."$exten"

if file --mime-type "download/$NAME/$NAME$FILECNT."$exten"" | grep -q zip$; then
if [ -f "/usr/bin/unzip" ];
then
unzip -O cp949 -oq download/$NAME/$NAME$FILECNT."$exten" -d download/$NAME/

LLOOPCNT=0
MAXC=$(ls download/$NAME/ | grep  ' '|wc -l)

while [ $LLOOPCNT -lt $MAXC ]
do
echo download/$NAME/\'$(ls download/$NAME |grep ' '|grep '.c'|awk 'FNR==1')\' download/$NAME/$(ls download/$NAME/ |grep ' ' |grep '.c' |awk 'FNR==1'|sed 's/ //g') |xargs mv
LLOOPCNT=$((LLOOPCNT + 1 ))
done
########################################################################################################################

######################바꿀 문자##########################################################################################
sed -i "s/${CHSTR[0]}/${CHSTR[1]}/g" download/$NAME/*
sed -i "s/${CHSTR_1[0]}/${CHSTR_1[1]}/g" download/$NAME/*
#########################################################################################################################
LLOOPCNT=1
COMPILE=$(ls download/$NAME | grep '..c'|cut -d. -f1|wc -l)

while [ $LLOOPCNT -le $COMPILE ]
do
gcc -lm -o download/$NAME/a."$(ls download/$NAME |grep '..c'| awk -v var=$LLOOPCNT 'FNR==var'|cut -d. -f1)"  "download/$NAME/$(ls download/$NAME |grep '..c'| awk -v var=$LLOOPCNT 'FNR==var')" >> download/$NAME/Compile_log.txt 2>&1
LLOOPCNT=$((LLOOPCNT + 1 ))
done


CNT_L=1

LLOOPCNT=$((LLOOPCNT - 1 ))
while [ $CNT_L -le $LLOOPCNT ]
do
QUESTION_NUM=$(ls download/$NAME/ -F|grep '[*]' |egrep -o '[^0-9][0-9][^0-9]||[^0-9][0-9][0-9][^0-9]'|egrep -o '[0-9]|[0-9][0-9]'|awk -v var=$CNT_L 'FNR==var')
SIMUL="std_"$QUESTION_NUM"_in"

if [ -f "$SIMUL" ] ; then
cat "download/$NAME/$(ls download/$NAME/ -F|grep '[*]'|awk -v var=$CNT_L 'FNR==var'|cut -d. -f2|cut -d* -f1).c" >> download/$NAME/SIMUL.txt 2>&1
echo "-----------------------------------------------------------------------------" >> download/$NAME/SIMUL.txt 2>&1
echo "-----------------------------------------------------------------------------" >> download/$NAME/SIMUL.txt 2>&1

timeout 0.1 ./download/$NAME/"$(ls download/$NAME/ -F|grep '[*]'|awk -v var=$CNT_L 'FNR==var'|cut -d* -f1)" < $SIMUL >> download/$NAME/SIMUL.txt 2>&1
echo "-----------------------------------------------------------------------------" >> download/$NAME/SIMUL.txt 2>&1
echo "-----------------------------------------------------------------------------" >> download/$NAME/SIMUL.txt 2>&1
fi
CNT_L=$((CNT_L + 1 ))
done

fi
fi

if [ $FILECNT -lt $TOTAL_FILE   ]; then
FILECNT=$((FILECNT + 1 ))
else

LOOPCNT=$((LOOPCNT + 1))
FILECNT=1
fi

else
FAIL=$((FAIL + 1))
LOOPCNT=$((LOOPCNT + 1))
FILECNT=1
fi


done

rm "LSG" "sub_file_id.txt" "sub_file_name.txt" "$(date +'%Y%m%d').txt" "name_list.txt" "ID_LIST.txt" "Token" "cookies.txt" "Redirection"
#zip -r "output.zip" download >/dev/null 2>&1
echo "[성공] Total $TOTAL >> FAIL $FAIL"
else
echo "종료!"
fi
else
echo "인증실패 자격이 없거나 / 쿠키를 업데이트하세요!"
fi
else
echo "[실패] $COOKIES"를 찾지 못하였습니다.
fi
else
echo "[실패] 아주비비에 연결실패 ??????????망!ㅋㅋㅋ"
fi




