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
            <form method="post" action="login.php">
                <input id="default_focus" autocomplete="off" type="password" name="memo">
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
                    <p><a href="new.php">새로운 메모 생성</a></p>
                    <p><a href="config.php">메모 반대로 삽입</a></p>
                    <hr>
                    <p><a href="mailto:bae_alex@naver.com">의견이 있으세요?</a></p>
                    <p><a href="https://www.blex.kr/donate-kakaopay">커피한잔 사주세요!</a></p>
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
                    $dir = "./";
                    echo '<li><h5>작성된 메모 리스트</h5></li>';
                    if(file_exists($dir)) {
                        if($dh = opendir($dir)) {
                            while(($file = readdir($dh)) !== false) {
                                if(( $file !== '.well-known' && strpos($file,'-'))) {
                                    $fr = fopen("$file/memo.txt", "r");
                                    $text = fread($fr, filesize("$file/memo.txt"));
                                    $text = strip_tags($text);
                                    $descript = substr($text, 0, 30);
                                    echo "<li><p><a href='".$dir.$file."'>".$file."</a> : $descript...</p></li>";
                                }
                            }
                            closedir($dh);
                        }
                    } else {
                        echo "<p>ERROR / 제작자에게 <a href=\"mailto:bae_alex@naver.com\">문의</a>하세요.</p>";
                    }
                    echo "
                    <script type='text/javascript'>
                    document.getElementById('default_focus').placeholder = '로그인 되었습니다.';
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
        input_box = document.getElementById("input_box");
        $(window).scroll(function () {
            if ($(this).scrollTop() < 200) {
                input_box.style.position="absolute";
                input_box.style.top="70px";
                $("#input_box").removeClass("slide_bottom");
            } else {
                input_box.style.position="fixed";
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
