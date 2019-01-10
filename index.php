<!DOCTYPE html>
<html>
<head lang="ko">
    <title>NotePHPad</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="theme-color" content="#035">
    <link rel="icon" href="/assets/favicon.ico">
    <link rel="icon" type="image/png" href="/assets/favicon.png">
    <link rel="stylesheet" href="/assets/main.css">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.6.3/css/all.css" integrity="sha384-UHRtZLI+pbxtHCWp1t77Bi1L4ZtiqrqD80Kn4Z8NTSRyMA2Fd33n5dQ8lWUE00s/" crossorigin="anonymous">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.22.2/codemirror.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.22.2/theme/dracula.min.css">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/lodash.js/4.17.4/lodash.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.22.2/codemirror.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.22.2/addon/runmode/runmode.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.22.2/mode/meta.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.22.2/addon/mode/loadmode.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.22.2/addon/mode/overlay.min.js"></script>
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
                <a href="https://github.com/baealex/NotePHPad/blob/master/README.md" target="_blank"><i class="fas fa-info-circle"></i></a>
            </button>
        </div>
        <div class="menu_box">
            <button type="button">
                <a href="#Menu"><i class="fas fa-bars"></i></a>
            </button>
            <div class="menu_modal" id="Menu">
                <div>
                    <a class="close_btn" href="/"><i class="fas fa-times"></i></a>
                    <p><a href="#Source">소스코드 삽입</a></p>
                    <p><a href="mailto:bae_alex@naver.com">의견이 있으세요?</a></p>
                    <p><a href="https://www.blex.kr/donate.png" target="_blank">커피한잔 사주세요!</a></p>
                    <hr>
                </div>
            </div>
            <div class="source_modal" id="Source">
                <div>
                    <form method="post" action="write.php">
                        <textarea id="source_code" name="source" placeholder="```&#13;&#10;#include <iostream>&#13;&#10;int main(void)&#13;&#10;{&#13;&#10;    int a = 0;&#13;&#10;    std::cout << a << std::endl;&#13;&#10;    return 0;&#13;&#10;}&#13;&#10;```"></textarea>
                        <p>
                            <button name="submit" id="submit"><i class="fas fa-check"></i></button>
                            <a class="close_btn" href="/"><i class="fas fa-times"></i></a>
                        </p>
                    </form>
                </div>
            </div>
        </div>
        <div class="content">
            <?php
                session_start();
                if(!isset($_SESSION['auth'])) {
                    readfile("basic.txt");
                    echo "
                    <script type='text/javascript'>
                    document.getElementById('default_focus').placeholder = '권한이 없습니다. 로그인해 주세요.';
                    </script>";
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
    <script type="text/javascript">
    var textarea = document.getElementById('source_code');
    var editor = CodeMirror.fromTextArea(textarea, {
        lineNumbers: true,
        lineWrapping: true,
        theme: "dracula",
        val: textarea.value
    });
    </script>
</body>
</html>