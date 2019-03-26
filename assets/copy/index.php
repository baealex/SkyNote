<!DOCTYPE html>
<html>
<head lang="ko">
<?php include_once '../assets/layout/head.html'?>
    <link rel="icon" href="../assets/favicon.ico">
    <link rel="icon" type="image/png" href="../assets/favicon.png">
    <link rel="stylesheet" href="../assets/main.css">
</head>
<body>
    <div id="body">
        <div id="input_box">
            <form method="post" action="write.php">
                <input id="default_focus" autocomplete="off" type="text" name="memo">
            </form>
        </div>
        <div class="info_box">
            <button type="button">
                <a href="../"><i class="fas fa-home"></i></a>
            </button>
        </div>
        <div class="menu_box">
            <button type="button">
                <a href="#Menu"><i class="fas fa-bars"></i></a>
            </button>
            <div class="menu_modal" id="Menu">
                <div>
                    <a class="close_btn" href="./"><i class="fas fa-times"></i></a>
                    <p><a href="#Source">소스코드 삽입</a></p>
                    <hr>
                    <p><a href="mailto:im@baejino.com">의견이 있으세요?</a></p>
                    <p><a href="https://baejino.com/assets/images/donate.png">커피한잔 사주세요!</a></p>
                </div>
            </div>
            <div class="source_modal" id="Source">
                <div>
                    <form method="post" action="write.php">
                        <textarea id="source_code" name="source" placeholder="```&#13;&#10;#include <iostream>&#13;&#10;int main(void)&#13;&#10;{&#13;&#10;    int a = 0;&#13;&#10;    std::cout << a << std::endl;&#13;&#10;    return 0;&#13;&#10;}&#13;&#10;```"></textarea>
                        <p>
                            <button name="submit" id="submit"><i class="fas fa-check"></i></button>
                            <a class="close_btn" href="./"><i class="fas fa-times"></i></a>
                        </p>
                    </form>
                </div>
            </div>
        </div>
        <div class="content">
            <?php
                session_start();
                if(!isset($_SESSION['auth'])) {
                    echo "<script>document.location.href='/';</script>";
                }
                else {
                    readfile("memo.txt");
                    echo "
                    <script type='text/javascript'>
                    document.getElementById('default_focus').placeholder = '메모 입력 후 엔터!';
                    </script>";
                }
            ?>
        </div>
    </div>
    <?php include_once '../assets/layout/footer.html'?>
    <?php
        $fr = fopen("../assets/config.ini", "r");
        $config = fread($fr, filesize("../assets/config.ini"));
        if($config == 1) {
            echo "<script>window.scrollTo(0,screen.height+9999);</script>";
        }
    ?>
</body>
</html>