<?php 
/**
 * @author LovkiY
 * @copyright 2012
 * 
 * Class_name Page for this controller.
 *	 
 */
  session_start();

  $uid=session_id();
  $item_id=$_POST["item_id"];
  $property = $_POST['property_array'];  

  for($z=0;$z<sizeof($_SESSION['cart'][$item_id]);$z++):
        if($_SESSION['cart'][$item_id][$z]['property']===$property):   
            array_splice($_SESSION['cart'][$item_id], $z, 1);             
        endif;
  endfor; 