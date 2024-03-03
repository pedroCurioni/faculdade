from __future__ import annotations

import tempfile

import easyocr
import fitz
from langchain.docstore.document import Document


def pdf_ocr_loader(file_path: str) -> list[Document]:
    document_list = []

    reader = easyocr.Reader(["pt"])

    with fitz.open(file_path) as doc:
        for page_num in range(len(doc)):
            page = doc.load_page(page_num)
            pix = page.get_pixmap()

            with tempfile.TemporaryDirectory() as temp_dir:
                pix.save(f"{temp_dir}/tmp.png", "png")
                result = reader.readtext(f"{temp_dir}/tmp.png")

            extracted_text = " ".join([i[1] for i in result])

            document_text = Document(extracted_text, metadata={"page": page_num})

            document_list.append(document_text)

    return document_list
