<?php
    include "./lib/parsedown.php";
    
    $memo = $_POST['memo'];
    $date = $_POST['date'];
    $is_source = $_POST['is_source'];

    echo "<script>alert('$is_source')</script>"; 

    $fr = fopen("./".$date."/memo.txt", "r");
    $text = fread($fr, filesize("./".$date."/memo.txt"));

    if($memo == "로그아웃" || $memo == "잠금") {
        session_start();
        unset($_SESSION['auth']);
        session_destroy();
        echo "<script>alert('잘가요. 관리자님 ;)')</script>"; 
    }

    else {
        session_start();
        if(!isset($_SESSION['auth'])) {
            echo "<script>alert('수정 권한이 없습니다 :(')</script>"; 
        }
        else {
            if($memo == "모든 메모 삭제") {
                $fw = fopen("./".$date."/memo.txt", "w");
                fwrite($fw, "");
                fclose($fw);
            }
            else if($memo == "현재 메모 다운") {
                $GetLink = './".$date."/memo.txt';
                $maxRead = 1 * 1024 * 1024;
                $DownlooadName = $date.'.txt';
                $fh = fopen($GetLink, 'r');
                header('Content-Type: application/octet-stream');
                header('Content-Disposition: attachment; filename="'.$DownlooadName.'"');
                while (!feof($fh)) {
                    echo fread($fh, $maxRead);
                    ob_flush();
                }
                exit;
            }
	        else {
                if(strpos($memo, '<') !== false) {
                    $memo = str_replace('<', '&lt;', $memo);
                }
                if(strpos($memo, '>') !== false) {
                    $memo = str_replace('>', '&gt;', $memo);
                }

                $Parsedown = new Parsedown();

                if($memo == '') {
                    $memo = "<p><br/></p>";
                }
                else if($is_source == 'true') {
                    $memo = $Parsedown->text("```\n$memo\n```");
                }
                else {
                    $memo = $Parsedown->text("$memo");
                }

                $fr = fopen("./assets/config.ini", "r");
                $config = fread($fr, filesize("./assets/config.ini"));

                $fw = fopen("./".$date."/memo.txt", "w");
                if($config == 1) {
                    fwrite($fw, $text."\n$memo");
                }
                else {
                    fwrite($fw, "$memo\n".$text);
                }
                fclose($fw);
            }
        }
    }

    echo readfile("./".$date."/memo.txt");
?>