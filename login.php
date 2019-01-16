<?php
    extract($_POST);

    if($memo == "난 파도가 머물던 모래 위에 적힌 글씨처럼") {
        session_start();
        $_SESSION['auth'] = "auth-success";
        echo "<script>alert('안녕하세요. 관리자님 :)')</script>"; 
    }

    else if($memo == "로그아웃" || $memo == "잠금") {
        session_start();
        unset($_SESSION['auth']);
        session_destroy();
        echo "<script>alert('잘가요. 관리자님 ;)')</script>"; 
    }

    else {
        session_start();
        if(!isset($_SESSION['auth'])) {
            echo "<script>alert('패스워드가 틀렸습니다 :(')</script>";
        }
        else {
            echo "<script>alert('이곳엔 메모를 작성할 수 없어요 :(')</script>";
        }
    }
    echo "<script>document.location.href='/';</script>"; 
?>