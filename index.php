<!DOCTYPE html>
<html>
<head lang="ko">
    <title>NotePHPad</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="theme-color" content="#035">
    <link rel="stylesheet" href="/assets/main.css">
    <link rel="icon" href="/assets/favicon.ico">
    <link rel="icon" type="image/png" href="/assets/favicon.png">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.6.3/css/all.css" integrity="sha384-UHRtZLI+pbxtHCWp1t77Bi1L4ZtiqrqD80Kn4Z8NTSRyMA2Fd33n5dQ8lWUE00s/" crossorigin="anonymous">
</head>
<body>
    <div id="body">
        <div id="input_box">
            <form method="post" action="write.php">
                <input id="default_focus" autocomplete="off" type="text" name="memo" placeholder="메모를 입력하고 엔터!">
            </form>
        </div>

        <div class="content">
            <?php
                session_start();
                if(!isset($_SESSION['auth'])) {
                    echo "<li>볼 수 있는 권한이 없습니다.</li><li>로그인을 해주세요!</li>"; 
                }
                else {
                    readfile("memo.txt");
                }
            ?>
        </div>
    </div>
    <footer>
        <p>Copyright &copy; 2019 <a href="https://www.blex.kr">BLEX.</a></p>
    </footer>
    <script type="text/javascript">
        document.getElementById('default_focus').focus();
    </script>
    <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script> 
    <script type="text/javascript">
    $(document).ready(function(){ 
        var mql = window.matchMedia("screen and (max-width: 1200px)");

        input_box = document.getElementById("input_box");
        body = document.getElementById("body");
        $(window).scroll(function () {
            if ($(this).scrollTop() < 200) {
                body.style.marginTop="70px";
                input_box.style.position="relative";
                input_box.style.width="100%";
                input_box.style.top="0px";
                $("#input_box").removeClass("slide_bottom");
            } else {
                if (mql.matches) {
                    body.style.marginTop="140px";
                } else {
                    body.style.marginTop="170px";
                }
                input_box.style.position="fixed";
                if (mql.matches) {
                    input_box.style.width="95%";
                } else {
                    input_box.style.width="50%";
                }
                input_box.style.top="-10px";
                $("#input_box").addClass("slide_bottom");
            }
        }); 
    }); 
    </script>
</body>
</html>