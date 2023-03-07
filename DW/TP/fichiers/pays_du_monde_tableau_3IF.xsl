<?xml version="1.0" encoding="UTF-8"?>

<!-- New XSLT document created with EditiX XML Editor (http://www.editix.com) at Tue Mar 07 15:47:44 CET 2023 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="html"/>
	
	
<xsl:template match="/"> 
		<html> 
		 <head> 
		 	<title> 
		 		Countries of the world 
		 	</title> 
		 </head> 
		 
		 <body style="background-color:white;"> 
		 	<h1>Information about the countries</h1> 
		 	<xsl:apply-templates select="countries/metadonnees"/>
		 	Styled by: Zijing Weng, Alexandre Rosard, Mohamed Saied Hmidi(B3331)
		 	<table border="3" width="100%" align="center">
		 		<th>N°</th>
		 		<th>Name</th>
		 		<th>Capital</th>
		 		<th>Coordinates</th>
		 		<th>Neighbours</th>
		 		<th>Flag</th>
		 		<th>Spoken languages</th>
		 		<xsl:apply-templates select="countries/country"/>
		 	</table>
		 </body> 
		</html> 
	</xsl:template>
	
	
<xsl:template match="metadonnees">
	 <p style="text-align:center; color:green;">
		Objectif : <xsl:value-of select="objectif"/>
	 </p><hr/>		
	</xsl:template>
	
	<xsl:template match="country"> 
		<tr>
			<td>
				<xsl:value-of select="position()"/>
			</td>
			<td>
				<span style="color: green">
					<xsl:value-of select="country_name/offic_name"/>
				</span> 
				(<xsl:value-of select="country_name/common_name"/>)
				
				<xsl:if test="count(country_name/native_name[@lang=&quot;fra&quot;])  &gt; 0">
					<br/>
					<span style="color: blue">
						Nom francais : <xsl:value-of select="country_name/native_name[@lang=&quot;fra&quot;]/offic_name"/>
					</span>
				</xsl:if>
			</td>
			<td>
				<xsl:value-of select="capital"/>
			</td>
			<td>
				Latitude : <xsl:value-of select="coordinates/@lat"/>
				<br/>
				Longitude : <xsl:value-of select="coordinates/@long"/>
			</td>
			<td>
				<xsl:if test="count(borders/neighbour)=0 and landlocked=&quot;false&quot;">
					Island
				</xsl:if>
				<xsl:if test="count(borders/neighbour) &gt; 0">
					<xsl:apply-templates select="borders"/>
				</xsl:if>
			</td>
		</tr>
	</xsl:template>
	
	<xsl:template match="borders">
		<xsl:for-each select="neighbour">
			<xsl:if test="position() &gt; 1">
				,
			</xsl:if>
			<xsl:variable name="cca3-code" select="."/>
			<xsl:value-of select="../../../country[./country_codes/cca3=$cca3-code]/country_name/common_name"/>
		</xsl:for-each>
	</xsl:template>
	
</xsl:stylesheet>


