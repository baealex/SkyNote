<!DOCTYPE html>
<html>
<head lang="ko">
    <?php include_once 'assets/layout/head.html'?>
    <link rel="icon" href="./assets/favicon.ico">
    <link rel="icon" type="image/png" href="./assets/favicon.png">
    <link rel="stylesheet" href="./assets/main.css">
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
                    <a class="close_btn" href="./"><i class="fas fa-times"></i></a>
                    <p><a href="new.php">새로운 메모 생성</a></p>
                    <p><a href="config.php">메모 반대로 삽입</a></p>
                    <hr>
                    <p><a href="mailto:im@baejino.com">의견이 있으세요?</a></p>
                    <p><a href="https://baejino.com/assets/images/donate.png">커피한잔 사주세요!</a></p>
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
                        echo "<p>ERROR / 제작자에게 <a href=\"mailto:im@baejino.com\">문의</a>하세요.</p>";
                    }
                    echo "
                    <script type='text/javascript'>
                    document.getElementById('default_focus').placeholder = '로그인 되었습니다.';
                    </script>";
                }
            ?>
        </div>
    </div>
    <?php include_once 'assets/layout/footer.html'?>
</body>
</html>