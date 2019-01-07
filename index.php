<!DOCTYPE html>
<html>
<head lang="ko">
    <title>메모장</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="theme-color" content="#035">
    <link rel="stylesheet" href="./style.css">
    <link rel="icon" href="./favicon.ico">
    <link rel="icon" type="image/png" href="./favicon.png" />
</head>
<body>
    <div class="body">
        <div class="input_box">
        <form method="post" action="write.php">
            <input id="default_focus" class="input_text" autocomplete="off" type="text" name="memo" placeholder="메모 작성하고 엔터!">
        </form>
        </div>
        <div class="content">
        <?php readfile("memo.txt"); ?>
        </div>
    </div>
    <footer>
        <p>Copyright &copy; 2018 <a href="https://www.blex.kr">BLEX.</a></p>
    </footer>
    <script type="text/javascript">
    document.getElementById('default_focus').focus();
    </script>
</body>
</html>