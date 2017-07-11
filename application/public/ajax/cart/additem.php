<?php 
/**
 * @author LovkiY
 * @copyright 2012
 * 
 * 
 *	 
 */
     
session_start();

require_once '../../../config/constants.inc';     
require_once CORE.'controllers/config.class.inc';
$config = new config();
require_once CORE.'controllers/db.class.inc';    

$uid=session_id();
$item_id=$_POST["item_id"];
$property = $_POST['property_array'];
$property = ltrim($property,',');
$property = rtrim($property,',');

if(!empty($_SESSION['cart'][$item_id])):
    $count=1;
    for($z=0;$z<sizeof($_SESSION['cart'][$item_id]);$z++):
        if($_SESSION['cart'][$item_id][$z]['property']==$property):
            $_SESSION['cart'][$item_id][$z]['qty']+= 1;
        else:
            $count++;
        endif;
    endfor;
    if($count>sizeof($_SESSION['cart'][$item_id])):
        $_SESSION['cart'][$item_id][$count-1]['qty'] = 1;
        $_SESSION['cart'][$item_id][$count-1]['property'] = $property;
    endif;
  
    $str = "Товар добавлен в корзину.";
else:    
    $_SESSION['cart'][$item_id][0]['qty'] = 1;
    $_SESSION['cart'][$item_id][0]['property'] = $property;
    $str = "Товар добавлен в корзину.";
endif;
//print_r($_SESSION);

$user_quantity = '';
foreach ($_SESSION['cart'] as $item=>$val): 
    for($y=0;$y<sizeof($val);$y++):
        $user_quantity+=$val[$y]['qty'];
    endfor;    
    $items[] = $item; 
endforeach;

$items = implode(',',$items);

$products = db::GetAll("SELECT id,price FROM catalogue_products WHERE id IN ({$items})");
$user_summ = '';
for($x=0;$x<sizeof($products);$x++):
    for($k=0;$k<sizeof($_SESSION['cart'][$products[$x]['id']]);$k++):
        $item_qty+=$_SESSION['cart'][$products[$x]['id']][$k]['qty'];
    endfor;
    $user_summ+= $products[$x]['price'] * $item_qty;
    unset($item_qty);
endfor;

unset($config);
echo $str."/".$user_quantity."/".$user_summ;  