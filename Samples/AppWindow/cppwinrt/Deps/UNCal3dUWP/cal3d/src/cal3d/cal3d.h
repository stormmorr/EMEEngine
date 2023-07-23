//****************************************************************************//
// cal3d.h                                                                    //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_CAL3D_H
#define CAL_CAL3D_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/animation.h"
#include "cal3d/animation_action.h"
#include "cal3d/animation_cycle.h"
#include "cal3d/bone.h"
#include "cal3d/coreanimation.h"
#include "cal3d/corebone.h"
#include "cal3d/corematerial.h"
#include "cal3d/coremesh.h"
#include "cal3d/coremodel.h"
#include "cal3d/coremorphanimation.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/coresubmesh.h"
#include "cal3d/coresubmorphtarget.h"
#include "cal3d/datasource.h"
#include "cal3d/error.h"
#include "cal3d/hardwaremodel.h"
#include "cal3d/loader.h"
#include "cal3d/matrix.h"
#include "cal3d/mesh.h"
#include "cal3d/mixer.h"
#include "cal3d/model.h"
#include "cal3d/morphtargetmixer.h"
#include "cal3d/physique.h"
#include "cal3d/physiquedualquaternion.h"
#include "cal3d/platform.h"
#include "cal3d/quaternion.h"
#include "cal3d/renderer.h"
#include "cal3d/saver.h"
#include "cal3d/skeleton.h"
#include "cal3d/springsystem.h"
#include "cal3d/streamsource.h"
#include "cal3d/submesh.h"
#include "cal3d/vector.h"

#endif

 /*****************************************************************************/
/** \mainpage Qun3D API Reference
  * <center>
  *   <p>
  *   &copy; 2001 - 2006 Laurent Desmecht, Loic Dachary, Bruno Heidelberger
  *   <p>
  *     Answers to many frequently asked questions about Qun3D can be found
  *     in the <a href="./cal3dfaq.html">Qun3D FAQ</a>.
  *   <p>
  *     Permission is granted to copy, distribute and/or modify this document
  *     under the terms of the GNU Free Documentation License, Version 1.1 or
  *     any later version published by the Free Software Foundation;
  *     A copy of the license is included in the section entitled
  *     \link license "GNU Free Documentation License" \endlink .
  * </center>
  *****************************************************************************/

 /*****************************************************************************/
/** \page license GNU Free Documentation License
  * Version 1.1, March 2000
  * <p>
  * Copyright (C) 2000  Free Software Foundation, Inc.<BR>
  * 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA<BR>
  * Everyone is permitted to copy and distribute verbatim copies<BR>
  * of this license document, but changing it is not allowed.<BR>
  * <p>
  * <strong>0. PREAMBLE</strong>
  * <p>
  * The purpose of this License is to make a manual, textbook, or other
  * written document "free" in the sense of freedom: to assure everyone
  * the effective freedom to copy and redistribute it, with or without
  * modifying it, either commercially or noncommercially.  Secondarily,
  * this License preserves for the author and publisher a way to get
  * credit for their work, while not being considered responsible for
  * modifications made by others.
  * <p>
  * This License is a kind of "copyleft", which means that derivative
  * works of the document must themselves be free in the same sense.  It
  * complements the GNU General Public License, which is a copyleft
  * license designed for free software.
  * <p>
  * We have designed this License in order to use it for manuals for free
  * software, because free software needs free documentation: a free
  * program should come with manuals providing the same freedoms that the
  * software does.  But this License is not limited to software manuals;
  * it can be used for any textual work, regardless of subject matter or
  * whether it is published as a printed book.  We recommend this License
  * principally for works whose purpose is instruction or reference.
  * <p>
  *
  * <strong>1. APPLICABILITY AND DEFINITIONS</strong>
  * <p>
  * This License applies to any manual or other work that contains a
  * notice placed by the copyright holder saying it can be distributed
  * under the terms of this License.  The "Document", below, refers to any
  * such manual or work.  Any member of the public is a licensee, and is
  * addressed as "you".
  * <p>
  * A "Modified Version" of the Document means any work containing the
  * Document or a portion of it, either copied verbatim, or with
  * modifications and/or translated into another language.
  * <p>
  * A "Secondary Section" is a named appendix or a front-matter section of
  * the Document that deals exclusively with the relationship of the
  * publishers or authors of the Document to the Document's overall subject
  * (or to related matters) and contains nothing that could fall directly
  * within that overall subject.  (For example, if the Document is in part a
  * textbook of mathematics, a Secondary Section may not explain any
  * mathematics.)  The relationship could be a matter of historical
  * connection with the subject or with related matters, or of legal,
  * commercial, philosophical, ethical or political position regarding
  * them.
  * <p>
  * The "Invariant Sections" are certain Secondary Sections whose titles
  * are designated, as being those of Invariant Sections, in the notice
  * that says that the Document is released under this License.
  * <p>
  * The "Cover Texts" are certain short passages of text that are listed,
  * as Front-Cover Texts or Back-Cover Texts, in the notice that says that
  * the Document is released under this License.
  * <p>
  * A "Transparent" copy of the Document means a machine-readable copy,
  * represented in a format whose specification is available to the
  * general public, whose contents can be viewed and edited directly and
  * straightforwardly with generic text editors or (for images composed of
  * pixels) generic paint programs or (for drawings) some widely available
  * drawing editor, and that is suitable for input to text formatters or
  * for automatic translation to a variety of formats suitable for input
  * to text formatters.  A copy made in an otherwise Transparent file
  * format whose markup has been designed to thwart or discourage
  * subsequent modification by readers is not Transparent.  A copy that is
  * not "Transparent" is called "Opaque".
  * <p>
  * Examples of suitable formats for Transparent copies include plain
  * ASCII without markup, Texinfo input format, LaTeX input format, SGML
  * or XML using a publicly available DTD, and standard-conforming simple
  * HTML designed for human modification.  Opaque formats include
  * PostScript, PDF, proprietary formats that can be read and edited only
  * by proprietary word processors, SGML or XML for which the DTD and/or
  * processing tools are not generally available, and the
  * machine-generated HTML produced by some word processors for output
  * purposes only.
  * <p>
  * The "Title Page" means, for a printed book, the title page itself,
  * plus such following pages as are needed to hold, legibly, the material
  * this License requires to appear in the title page.  For works in
  * formats which do not have any title page as such, "Title Page" means
  * the text near the most prominent appearance of the work's title,
  * preceding the beginning of the body of the text.
  * <p>
  *
  * <strong>2. VERBATIM COPYING</strong>
  * <p>
  * You may copy and distribute the Document in any medium, either
  * commercially or noncommercially, provided that this License, the
  * copyright notices, and the license notice saying this License applies
  * to the Document are reproduced in all copies, and that you add no other
  * conditions whatsoever to those of this License.  You may not use
  * technical measures to obstruct or control the reading or further
  * copying of the copies you make or distribute.  However, you may accept
  * compensation in exchange for copies.  If you distribute a large enough
  * number of copies you must also follow the conditions in section 3.
  * <p>
  * You may also lend copies, under the same conditions stated above, and
  * you may publicly display copies.
  * <p>
  *
  * <strong>3. COPYING IN QUANTITY</strong>
  * <p>
  * If you publish printed copies of the Document numbering more than 100,
  * and the Document's license notice requires Cover Texts, you must enclose
  * the copies in covers that carry, clearly and legibly, all these Cover
  * Texts: Front-Cover Texts on the front cover, and Back-Cover Texts on
  * the back cover.  Both covers must also clearly and legibly identify
  * you as the publisher of these copies.  The front cover must present
  * the full title with all words of the title equally prominent and
  * visible.  You may add other material on the covers in addition.
  * Copying with changes limited to the covers, as long as they preserve
  * the title of the Document and satisfy these conditions, can be treated
  * as verbatim copying in other respects.
  * <p>
  * If the required texts for either cover are too voluminous to fit
  * legibly, you should put the first ones listed (as many as fit
  * reasonably) on the actual cover, and continue the rest onto adjacent
  * pages.
  * <p>
  * If you publish or distribute Opaque copies of the Document numbering
  * more than 100, you must either include a machine-readable Transparent
  * copy along with each Opaque copy, or state in or with each Opaque copy
  * a publicly-accessible computer-network location containing a complete
  * Transparent copy of the Document, free of added material, which the
  * general network-using public has access to download anonymously at no
  * charge using public-standard network protocols.  If you use the latter
  * option, you must take reasonably prudent steps, when you begin
  * distribution of Opaque copies in quantity, to ensure that this
  * Transparent copy will remain thus accessible at the stated location
  * until at least one year after the last time you distribute an Opaque
  * copy (directly or through your agents or retailers) of that edition to
  * the public.
  * <p>
  * It is requested, but not required, that you contact the authors of the
  * Document well before redistributing any large number of copies, to give
  * them a chance to provide you with an updated version of the Document.
  * <p>
  *
  * <strong>4. MODIFICATIONS</strong>
  * <p>
  * You may copy and distribute a Modified Version of the Document under
  * the conditions of sections 2 and 3 above, provided that you release
  * the Modified Version under precisely this License, with the Modified
  * Version filling the role of the Document, thus licensing distribution
  * and modification of the Modified Version to whoever possesses a copy
  * of it.  In addition, you must do these things in the Modified Version:
  * <p>
  * <ul>
  * <li><strong>A.</strong> Use in the Title Page (and on the covers, if any) a title distinct
  *    from that of the Document, and from those of previous versions
  *    (which should, if there were any, be listed in the History section
  *    of the Document).  You may use the same title as a previous version
  *    if the original publisher of that version gives permission.
  * <li><strong>B.</strong> List on the Title Page, as authors, one or more persons or entities
  *    responsible for authorship of the modifications in the Modified
  *    Version, together with at least five of the principal authors of the
  *    Document (all of its principal authors, if it has less than five).
  * <li><strong>C.</strong> State on the Title page the name of the publisher of the
  *    Modified Version, as the publisher.
  * <li><strong>D.</strong> Preserve all the copyright notices of the Document.
  * <li><strong>E.</strong> Add an appropriate copyright notice for your modifications
  *    adjacent to the other copyright notices.
  * <li><strong>F.</strong> Include, immediately after the copyright notices, a license notice
  *    giving the public permission to use the Modified Version under the
  *    terms of this License, in the form shown in the Addendum below.
  * <li><strong>G.</strong> Preserve in that license notice the full lists of Invariant Sections
  *    and required Cover Texts given in the Document's license notice.
  * <li><strong>H.</strong> Include an unaltered copy of this License.
  * <li><strong>I.</strong> Preserve the section entitled "History", and its title, and add to
  *    it an item stating at least the title, year, new authors, and
  *    publisher of the Modified Version as given on the Title Page.  If
  *    there is no section entitled "History" in the Document, create one
  *    stating the title, year, authors, and publisher of the Document as
  *    given on its Title Page, then add an item describing the Modified
  *    Version as stated in the previous sentence.
  * <li><strong>J.</strong> Preserve the network location, if any, given in the Document for
  *    public access to a Transparent copy of the Document, and likewise
  *    the network locations given in the Document for previous versions
  *    it was based on.  These may be placed in the "History" section.
  *    You may omit a network location for a work that was published at
  *    least four years before the Document itself, or if the original
  *    publisher of the version it refers to gives permission.
  * <li><strong>K.</strong> In any section entitled "Acknowledgements" or "Dedications",
  *    preserve the section's title, and preserve in the section all the
  *    substance and tone of each of the contributor acknowledgements
  *    and/or dedications given therein.
  * <li><strong>L.</strong> Preserve all the Invariant Sections of the Document,
  *    unaltered in their text and in their titles.  Section numbers
  *    or the equivalent are not considered part of the section titles.
  * <li><strong>M.</strong> Delete any section entitled "Endorsements".  Such a section
  *    may not be included in the Modified Version.
  * <li><strong>N.</strong> Do not retitle any existing section as "Endorsements"
  *    or to conflict in title with any Invariant Section.
  * </ul>
  * <p>
  * If the Modified Version includes new front-matter sections or
  * appendices that qualify as Secondary Sections and contain no material
  * copied from the Document, you may at your option designate some or all
  * of these sections as invariant.  To do this, add their titles to the
  * list of Invariant Sections in the Modified Version's license notice.
  * These titles must be distinct from any other section titles.
  * <p>
  * You may add a section entitled "Endorsements", provided it contains
  * nothing but endorsements of your Modified Version by various
  * parties--for example, statements of peer review or that the text has
  * been approved by an organization as the authoritative definition of a
  * standard.
  * <p>
  * You may add a passage of up to five words as a Front-Cover Text, and a
  * passage of up to 25 words as a Back-Cover Text, to the end of the list
  * of Cover Texts in the Modified Version.  Only one passage of
  * Front-Cover Text and one of Back-Cover Text may be added by (or
  * through arrangements made by) any one entity.  If the Document already
  * includes a cover text for the same cover, previously added by you or
  * by arrangement made by the same entity you are acting on behalf of,
  * you may not add another; but you may replace the old one, on explicit
  * permission from the previous publisher that added the old one.
  * <p>
  * The author(s) and publisher(s) of the Document do not by this License
  * give permission to use their names for publicity for or to assert or
  * imply endorsement of any Modified Version.
  * <p>
  *
  * <strong>5. COMBINING DOCUMENTS</strong>
  * <p>
  * You may combine the Document with other documents released under this
  * License, under the terms defined in section 4 above for modified
  * versions, provided that you include in the combination all of the
  * Invariant Sections of all of the original documents, unmodified, and
  * list them all as Invariant Sections of your combined work in its
  * license notice.
  * <p>
  * The combined work need only contain one copy of this License, and
  * multiple identical Invariant Sections may be replaced with a single
  * copy.  If there are multiple Invariant Sections with the same name but
  * different contents, make the title of each such section unique by
  * adding at the end of it, in parentheses, the name of the original
  * author or publisher of that section if known, or else a unique number.
  * Make the same adjustment to the section titles in the list of
  * Invariant Sections in the license notice of the combined work.
  * <p>
  * In the combination, you must combine any sections entitled "History"
  * in the various original documents, forming one section entitled
  * "History"; likewise combine any sections entitled "Acknowledgements",
  * and any sections entitled "Dedications".  You must delete all sections
  * entitled "Endorsements."
  * <p>
  *
  * <strong>6. COLLECTIONS OF DOCUMENTS</strong>
  * <p>
  * You may make a collection consisting of the Document and other documents
  * released under this License, and replace the individual copies of this
  * License in the various documents with a single copy that is included in
  * the collection, provided that you follow the rules of this License for
  * verbatim copying of each of the documents in all other respects.
  * <p>
  * You may extract a single document from such a collection, and distribute
  * it individually under this License, provided you insert a copy of this
  * License into the extracted document, and follow this License in all
  * other respects regarding verbatim copying of that document.
  * <p>
  *
  * <strong>7. AGGREGATION WITH INDEPENDENT WORKS</strong>
  * <p>
  * A compilation of the Document or its derivatives with other separate
  * and independent documents or works, in or on a volume of a storage or
  * distribution medium, does not as a whole count as a Modified Version
  * of the Document, provided no compilation copyright is claimed for the
  * compilation.  Such a compilation is called an "aggregate", and this
  * License does not apply to the other self-contained works thus compiled
  * with the Document, on account of their being thus compiled, if they
  * are not themselves derivative works of the Document.
  * <p>
  * If the Cover Text requirement of section 3 is applicable to these
  * copies of the Document, then if the Document is less than one quarter
  * of the entire aggregate, the Document's Cover Texts may be placed on
  * covers that surround only the Document within the aggregate.
  * Otherwise they must appear on covers around the whole aggregate.
  * <p>
  *
  * <strong>8. TRANSLATION</strong>
  * <p>
  * Translation is considered a kind of modification, so you may
  * distribute translations of the Document under the terms of section 4.
  * Replacing Invariant Sections with translations requires special
  * permission from their copyright holders, but you may include
  * translations of some or all Invariant Sections in addition to the
  * original versions of these Invariant Sections.  You may include a
  * translation of this License provided that you also include the
  * original English version of this License.  In case of a disagreement
  * between the translation and the original English version of this
  * License, the original English version will prevail.
  * <p>
  *
  * <strong>9. TERMINATION</strong>
  * <p>
  * You may not copy, modify, sublicense, or distribute the Document except
  * as expressly provided for under this License.  Any other attempt to
  * copy, modify, sublicense or distribute the Document is void, and will
  * automatically terminate your rights under this License.  However,
  * parties who have received copies, or rights, from you under this
  * License will not have their licenses terminated so long as such
  * parties remain in full compliance.
  * <p>
  *
  * <strong>10. FUTURE REVISIONS OF THIS LICENSE</strong>
  * <p>
  * The Free Software Foundation may publish new, revised versions
  * of the GNU Free Documentation License from time to time.  Such new
  * versions will be similar in spirit to the present version, but may
  * differ in detail to address new problems or concerns.  See
  * http://www.gnu.org/copyleft/.
  * <p>
  * Each version of the License is given a distinguishing version number.
  * If the Document specifies that a particular numbered version of this
  * License "or any later version" applies to it, you have the option of
  * following the terms and conditions either of that specified version or
  * of any later version that has been published (not as a draft) by the
  * Free Software Foundation.  If the Document does not specify a version
  * number of this License, you may choose any version ever published (not
  * as a draft) by the Free Software Foundation.
  *****************************************************************************/

//****************************************************************************//
