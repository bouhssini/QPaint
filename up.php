<?php
$user_db='root';
$passwd_db='Maqraa17rootMaqraa17';
$host_db='localhost';
$db_mysql='maahad_hakiba';
$link = NULL;

$link = mysql_connect($host_db, $user_db, $passwd_db);	


function generateRandomString($length = 10) {
    $characters = '-_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $charactersLength = strlen($characters);
    $randomString = '';
    for ($i = 0; $i < $length; $i++) {
        $randomString .= $characters[rand(0, $charactersLength - 1)];
    }
    return $randomString;
}

    function array_key_last(array $array){
        $i=0;
        foreach ($array as &$value) {
            $i++;
        }
        return $i;
    }


if(!empty($_FILES)) {
	if(is_uploaded_file($_FILES['userImage']['tmp_name']))
	{
        $id_usr = 0;
        $id_room = 0;

        if (isset($_POST['id_usr']))  $id_usr = (int)$_POST['id_usr'];
        if (isset($_POST['id_room']))  $id_room = (int)$_POST['id_room'];
   

		$sourcePath = $_FILES['userImage']['tmp_name'];
		$targetPath = "./images/" . $_FILES['userImage']['name'];

        
		if(move_uploaded_file($sourcePath,$targetPath)) {
			echo "\nfile:" . $targetPath . "\nOK";
			echo "\nid_usr:" . $id_usr;
			echo "\nid_room:" . $id_room;

            $hashnew = $_FILES['userImage']['name'];

            


            $sql = "SELECT * FROM `pal_sabora` WHERE `id_room` = $id_room;";
            $result = mysql_db_query($db_mysql, $sql, $link);
            $co = mysql_num_rows($result);
            if ( $co > 0){
                $row = mysql_fetch_array($result);
                $id = intval($row['id']);
                $hash = $row['pic_00'];
                $myFile = "./images/" . $hash;
                unlink($myFile);
                mysql_free_result($result);

                $sql = "UPDATE `pal_sabora` SET `id_room` = '$id_room', `id_usr` = '$id_usr', `pic_00` = '$hashnew' WHERE `id` = $id;";
                mysql_db_query($db_mysql, $sql, $link);
            }else{
                mysql_free_result($result);
                $sql = "INSERT INTO `pal_sabora` (`id`, `id_room`, `id_usr`, `id_sabora_doc`, `pic_00`, `pic_01`, `pic_02`, `pic_03`, `pic_04`, `pic_05`, `pic_06`, `pic_07`, `pic_08`, `pic_09`, `pic_10`, `pic_11`, `pic_12`, `pic_13`, `pic_14`, `pic_15`) VALUES (NULL, '$id_room', '$id_usr', '0', '$hashnew', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);";
                mysql_db_query($db_mysql, $sql, $link);

            }
            
            
		}else{
			echo "No move_uploaded_file";
		}
	}
}




	







?>

