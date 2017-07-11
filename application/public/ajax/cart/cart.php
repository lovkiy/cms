<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

session_start();

  $uid=session_id();
  $items=$_POST["items"];
  $property = $_POST['property_array'];  
  $qty = $_POST['qty'];
  $property = ltrim($property,'>>');
  
  $item_array = explode(',', $items); 
  $property_array = explode('>>', $property);
  $qty_array = explode(',', $qty); 
  
  print_r($item_array);
  print_r($property_array);
  print_r($qty_array);
 // unset($_SESSION['cart']);
  
  for($x=0;$x<sizeof($item_array);$x++): 
      for($z=0;$z<sizeof($_SESSION['cart'][$item_array[$x]]);$z++):          
            $properties = ($property_array[$x]!='0')? $property_array[$x] : '';           
            if($_SESSION['cart'][$item_array[$x]][$z]['property']===$properties):   
                $_SESSION['cart'][$item_array[$x]][$z]['qty'] = $qty_array[$x];             
            endif;
      endfor;
  endfor; 