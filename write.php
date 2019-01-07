<?php
    include "index.php";
    extract($_POST);

    $fr = fopen("./memo.txt", "r");
    $text = fread($fr, filesize("./memo.txt"));

    if($memo == "모든 메모를 삭제") {
        $fw = fopen("./memo.txt", "w");
        fwrite($fw, "");
        fclose($fw);
    }

    else {
        if(strpos($memo, '<a>') !== false) {

        }
        else if(strpos($memo, '<b>') !== false) {

        }
        else {
            if(strpos($memo, '<') !== false) {
                $memo = str_replace('<', '&lt;', $memo);
            }
            if(strpos($memo, '>') !== false) {
                $memo = str_replace('>', '&gt;', $memo);
            }
        }
        $fw = fopen("./memo.txt", "w");
        fwrite($fw, "<li>$memo</li>\n".$text);
        fclose($fw);
    }

    echo "<script>document.location.href='http://memo.blex.kr';</script>"; 
?>