<?php $breakpoint 		= $content['field_cm_ban_element_breakpoint']; ?>
<?php $breakpoint_max 	= $content['field_cm_ban_el_breakpoint_max']; ?>
<?php $element_size 	= $content['field_cm_ban_element_size']; ?>

<?php 
	hide($content['field_custom_banner_image']);
	hide($content['field_cm_banner_element_position']);
	hide($content['field_cm_ban_element_breakpoint']);
	hide($content['field_cm_ban_element_size']);
?>

<?php

$image_url 	= '';

//Til að fá atom id
$banner_image_item_id = $content['field_custom_banner_image']['#object']->item_id;
$atom_id 	= $content['field_custom_banner_image']['#items'][0]['sid'];

//til að ná í atom
$atom 		= scald_atom_load($atom_id);

if(!empty($atom)) {
        //Til að ná í myndaurlið í réttum stíl
	$image_url = image_style_url('custom_banner', $atom->file_source);
}

?>

<?php if (($breakpoint)&&($breakpoint_max)): ?>

	<div class="absolute-image-<?php print $banner_image_item_id; ?>">
		<style>
			@media only screen <?php print "and (min-width: " . render($breakpoint); ?>px) <?php print "and (max-width: " . render($breakpoint_max); ?>px){
				.absolute-image-<?php print $banner_image_item_id; ?> {
					background: url(<?php print $image_url; ?>) no-repeat;
					position: absolute; 
					<?php print render($content['field_cm_banner_element_position']); ?>
					
					<?php if ($element_size): ?>
						<?php print render($content['field_cm_ban_element_size']); ?>
					<?php else: ?>
						width: <?php print($atom->scald_thumbnail['und'][0]['metadata']['width']); ?>px;
						height: <?php print($atom->scald_thumbnail['und'][0]['metadata']['height']); ?>px;
					<?php endif; ?>
					
					background-size: contain;
				}
			}
		</style>
	</div>

<?php elseif ($breakpoint): ?>

	<div class="absolute-image-<?php print $banner_image_item_id; ?>">
		<style>
			@media only screen <?php print "and (min-width: " . render($breakpoint); ?>px) {
				.absolute-image-<?php print $banner_image_item_id; ?> {
					background: url(<?php print $image_url; ?>) no-repeat;
					position: absolute; 
					<?php print render($content['field_cm_banner_element_position']); ?>

					<?php if ($element_size): ?>
						<?php print render($content['field_cm_ban_element_size']); ?>
					<?php else: ?>
						width: <?php print($atom->scald_thumbnail['und'][0]['metadata']['width']); ?>px;
						height: <?php print($atom->scald_thumbnail['und'][0]['metadata']['height']); ?>px;
					<?php endif; ?>

					background-size: contain;
				}
			}
		</style>
	</div>

<?php elseif ($breakpoint_max): ?>

	<div class="absolute-image-<?php print $banner_image_item_id; ?>">
		<style>
			@media only screen <?php print "and (max-width: " . render($breakpoint_max); ?>px){
				.absolute-image-<?php print $banner_image_item_id; ?> {
					background: url(<?php print $image_url; ?>) no-repeat;
					position: absolute; 
					<?php print render($content['field_cm_banner_element_position']); ?>

					<?php if ($element_size): ?>
						<?php print render($content['field_cm_ban_element_size']); ?>
					<?php else: ?>
						width: <?php print($atom->scald_thumbnail['und'][0]['metadata']['width']); ?>px;
						height: <?php print($atom->scald_thumbnail['und'][0]['metadata']['height']); ?>px;
					<?php endif; ?>

					background-size: contain;
				}
			}
		</style>
	</div>

<?php else: ?>

	<div class="absolute-image-<?php print $banner_image_item_id; ?>" style="background: url(<?php print $image_url; ?>) no-repeat;
		
		<?php if ($element_size): ?>
			<?php print render($content['field_cm_ban_element_size']); ?>
		<?php else: ?>
			width: <?php print($atom->scald_thumbnail['und'][0]['metadata']['width']); ?>px;
			height: <?php print($atom->scald_thumbnail['und'][0]['metadata']['height']); ?>px;
		<?php endif; ?>

	background-size: contain;
	position: absolute; <?php print render($content['field_cm_banner_element_position']); ?>">
	</div>

<?php endif; ?>




